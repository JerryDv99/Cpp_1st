// Framework v 0.3
// 플레이어 몬스터 씬관리 투사체 *충돌* 거리/방향 구하기 

// Bullet이 몬스터와 충돌 시 Bullet 제거
#include "Headers.h"
// Space 미사일 여러개 만들기
int main(void)
{

	HideCursor(false); // 커서를 숨김

	// 배경 초기화
	
	DrawTextInfo BackGround[32];
	
	for (int i = 0; i < 32; ++i)
	{
		// 랜덤값을 초기화 해줌, 큰 값이 나올 수 있도록 time값끼리 곱해줄 것이지만
		// for문이 빠르게 돌게되면 time의 증가값보다 빠를 수 있기 때문에
		// 랜덤값이라고 하더라도 연속으로 같은 값이 나올 수 있음
		// i의 값을 곱하고 더해줌으로써 중복값이 나오지 않도록 해줌
		srand((GetTickCount() + i * i)* GetTickCount());


		// 현재 어떻게 사용할지 정하지 않았지만, 추후 배경과 총알을 구분지어 플레이어가 배경과 닿았을때
		// 총알에 닿았을 때에만 충돌판정이 되도록 설정해줄 것임
		BackGround[i].Info.Option = 0;

		// 좌표를 랜덤으로 설정
		BackGround[i].TransInfo.Position.x = rand() % 100 + 10;
		BackGround[i].TransInfo.Position.y = rand() % 26 + 1;

		BackGround[i].Info.Texture = (char*)"*";

		BackGround[i].Info.Color = rand() % 8 + 1;

	}

	// ** 플레이어 선언 및 동적할당
	Object* Player = new Object;

	// ** 플레이어 초기화
	Initialize(Player, (char*)"=>-", 30, 10);

	Object* Enemy[32]; // = new Object;
	Enemy[0] = new Object;
	Initialize(Enemy[0], (char*)"-<=", 80, 10);
	for (int i = 1; i < 32; ++i)
		Enemy[i] = nullptr;

	// 현재 시간으로 초기화
	ULONGLONG Time = GetTickCount64();
	ULONGLONG EnemyTime = GetTickCount64();
	ULONGLONG Cooling = GetTickCount64();
	ULONGLONG Err = GetTickCount64();

	int Score = 0;

	Object* Bullet[128] = { nullptr };
	Object* EBullet[128] = { nullptr };

	Object* Temp[128] = { nullptr };
	Vector3 Direction;
	
	bool Check = false;
	bool OHeat = false;
	float Power = 0.0f;

	// 출력
	while (true)
	{
		// 초기화된 시간부터 +50만큼 증가하면
		// 프레임과 프레임 사이의 시간 간격을 0.5초로 세팅
		if (Time + 80 < GetTickCount64())
		{
			// 증가된 값만큼 다시 초기화
			Time = GetTickCount64();

			system("cls");




			// ** 배경 출력
			for (int i = 0; i < 32; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);

				// ** 배경으로 사용될 텍스처의 색상을 랜덤으로 설정.
				BackGround[i].Info.Color = rand() % 8 + 1;
			}
			
			// Enemy 생성
			if (EnemyTime + 1000 < GetTickCount64())
			{
				EnemyTime = GetTickCount64();
				for (int i = 0; i < 32; ++i)
				{
					if (Enemy[i] == nullptr)
					{
						srand((GetTickCount() + i * i) * GetTickCount());
						Enemy[i] = CreateEnemy(115, rand()%30, EnemyTime);
						Enemy[i]->ETime = GetTickCount();

						break;
					}
				}

			}
			
			
			
			for (int i = 0; i < 32; ++i)
			{
				if (Enemy[i] != nullptr)				
				{
					srand((GetTickCount() + i * i) * GetTickCount());
					if (Enemy[i]->ETime + (rand() % 500 + 500) < GetTickCount64())
					{
						Enemy[i]->ETime = GetTickCount64();
						for (int j = 0; j < 128; ++j)
						{
							if (EBullet[j] == nullptr)
							{
								EBullet[j] = CreateBullet(
									Enemy[i]->TransInfo.Position.x - 2,
									Enemy[i]->TransInfo.Position.y);

								break;
							}
							
						}
					}
				}
			}

			/*for (int i = 0; i < 128; ++i)
			{
				if (EBullet[i] == nullptr)
				{
					for (int j = 0; j < 32; ++j)
					{
						if (Enemy[j] != nullptr)
						{	

							EBullet[i] = CreateBullet(
								Enemy[j]->TransInfo.Position.x - 2,
								Enemy[j]->TransInfo.Position.y);

							OnDrawText(i, 20.0f, 2.0f);
							OnDrawText(j, 30.0f, 2.0f);
							break;
							
						}
					}
				}break;
			}*/
			

			for (int i = 0; i < 128; ++i)
			{
				if (EBullet[i] != nullptr)
				{
					if (Collision(Player, EBullet[i]))
					{
						OnDrawText((char*)"으악",
							Player->TransInfo.Position.x - 2,
							Player->TransInfo.Position.y + 1, 10);
					
						delete EBullet[i];
						EBullet[i] = nullptr;
						break;
					}
					
					if (EBullet[i] != nullptr)
					{
						if (EBullet[i]->TransInfo.Position.x <= 1)
						{
							delete EBullet[i];
							EBullet[i] = nullptr;	// 반복문 안에서 delete는 위험
						}
					}
				}
			}

			// Bullet의 총 길이만큼 반복문으로 확인
			for (int i = 0; i < 128; ++i)
			{
				// 현재 생산된 Bulet만 확인
				if (Bullet[i] != nullptr)
				{
					// Enemy 전체 길이를 확인
					for (int j = 0; j < 32; ++j)
					{
						// 현재 생성된 Enemy만 확인
						if (Enemy[j] != nullptr)
						{
							// 위 루프까지 들어왔다면 Bullet과 Enemy는 현재 생산된 상태
							// 서로 충돌 확인
							if (Collision(Enemy[j], Bullet[i]))
							{
								// 충돌 발생시 둘 다 삭제
								delete Enemy[j];
								Enemy[j] = nullptr;

								delete Bullet[i];
								Bullet[i] = nullptr;

								// 반복문 탈출
								break;
							}
						}
					}

					// 생성된 Bullet 중에
					if (Bullet[i] != nullptr)
					{
						// Bullet이 콘솔 화면 이탈 시 삭제
						if (Bullet[i]->TransInfo.Position.x + Bullet[i]->TransInfo.Scale.x >= 120)
						{
							delete Bullet[i];
							Bullet[i] = nullptr;	// 보통 반복문 안에서의 delete는 위험
						}
					}
				}
			}
			
			//if (Collision(Player, Enemy))
				//OnDrawText((char*)"충돌 입니다.", Enemy->TransInfo.Position.x, Enemy->TransInfo.Position.y - 1, 12);
		
			UpdateInput(Player);

			/***********************************************************
			* 0x0000 이전에 눌린 적이 없고, 호출 시점에 눌리지 않은 상태
			* 0x8000 이전에 눌린 적이 없고, 호출 시점에 눌린 상태
			* 
			* 0x0001 이전에 눌린 적이 있고, 호출 시점에 눌리지 않은 상태
			* 0x8001 이전에 눌린 적이 있고, 호출 시점에 눌린 상태
			************************************************************/

			// 스페이스 키를 입력받음
			// 버튼을 눌렀을때
			if (OHeat == false)
			{
				
				if (!Check && GetAsyncKeyState(VK_SPACE) & 0x0001)
				{
					// 값 초기화
								
					Check = true;
				}
				// 버튼을 누르고 잇을떄
				if (GetAsyncKeyState(VK_SPACE) & 0x8000)
				{
					if (Power < 10)
						Power += 0.5f;
				}
				// 버튼을 누르지 않은 상태
				if (Check && !(GetAsyncKeyState(VK_SPACE) & 0x8000))
				{
				
					// 버튼을 놓았을 때 Temp 생성
					for (int i = 0; i < 128; i++)
					{
						if (Temp[i] == nullptr)
						{
							srand((GetTickCount() + i * i) * GetTickCount());

							Temp[i] = new Object;

							Temp[i]->TransInfo.Position.x = 0;
							Temp[i]->TransInfo.Position.y = float(rand() % 30);

							Temp[i]->Info.Texture = (char*)">-";

							Temp[i]->Speed = Power;

							Direction = GetDirection(Player, Temp[i]);
						
							Check = false;
							break;
						}
					}

				}
				if (Check == false)
				{
					if (Cooling + 1000 < GetTickCount64())
					{
						Cooling = GetTickCount64();
						Power -= 1.0f;
					}
				}
			}

			

			for (int i = 0; i < 128; ++i)
			{
				// 현재 생산된 Bulet만 확인
				if (Temp[i] != nullptr)
				{
					// Enemy 전체 길이를 확인
					for (int j = 0; j < 32; ++j)
					{
						// 현재 생성된 Enemy만 확인
						if (Enemy[j] != nullptr)
						{
							// 위 루프까지 들어왔다면 Bullet과 Enemy는 현재 생산된 상태
							// 서로 충돌 확인
							if (Collision(Enemy[j], Temp[i]))
							{
								// 충돌 발생시 둘 다 삭제
								delete Enemy[j];
								Enemy[j] = nullptr;

								delete Temp[i];
								Temp[i] = nullptr;

								// 반복문 탈출
								break;
							}
						}
					}

					// 생성된 Bullet 중에
					//if (Temp[i] != nullptr)
					//{
					//	// Bullet이 콘솔 화면 이탈 시 삭제
					//	if (Temp[i]->TransInfo.Position.x + Bullet[i]->TransInfo.Scale.x >= 117)
					//	{
					//		delete Temp[i];
					//		Temp[i] = nullptr;	// 보통 반복문 안에서의 delete는 위험
					//	}
					//}
				}
			}
			/*
			if (GetAsyncKeyState(VK_SPACE))
			{

				// Temp가 Player를 추척하기 위해 방향을 받아옴
				
				for (int i = 0; i < 128; ++i)
				{
					if (Bullet[i] == nullptr)
					{
						Bullet[i] = CreateBullet(
							Player->TransInfo.Position.x,
							Player->TransInfo.Position.y);
						break;
					}
				}
			}
			*/

			// Player 출력
			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);
			
			for (int i = 0; i < 128; ++i)
			{
				if (Temp[i] != nullptr)
				{
					OnDrawText(Temp[i]->Info.Texture,
						Temp[i]->TransInfo.Position.x,
						Temp[i]->TransInfo.Position.y,
						10);

					// 해당 방향으로 이동
					Temp[i]->TransInfo.Position.x += Direction.x * Temp[i]->Speed;
					//Temp->TransInfo.Position.y += Direction.y * Temp->Speed;

					// 거리 출력
					OnDrawText((char*)"Length : ", float(60 - strlen("Length : ")), 2.0f);
					OnDrawText((int)GetDistance(Player, Temp[i]), 60.0f, 2.0f);

					if (Temp[i]->TransInfo.Position.x >= 117)
					{
						delete Temp[i];
						Temp[i] = nullptr;
					}				
				}
			}

			for (int i = 0; i < 32; ++i)
			{
				if (Enemy[i])
				{
					Enemy[i]->TransInfo.Position.x--;

					// Enemy 출력
					OnDrawText(Enemy[i]->Info.Texture,
						Enemy[i]->TransInfo.Position.x,
						Enemy[i]->TransInfo.Position.y,
						12);
					//OnDrawText(i, Enemy[i]->TransInfo.Position.x, Enemy[i]->TransInfo.Position.y + 1);
					//  Enemy 스크린 충돌
					if (Enemy[i]->TransInfo.Position.x <= 0)
					{
						delete Enemy[i];
						Enemy[i] = nullptr;
					}
				}
				
			}

			

				

			// Bullet 출력
			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i])
				{
					Bullet[i]->TransInfo.Position.x += 2;

					OnDrawText(Bullet[i]->Info.Texture,
						Bullet[i]->TransInfo.Position.x,
						Bullet[i]->TransInfo.Position.y);
				}
			}

			for (int i = 0; i < 128; ++i)
			{
				if (EBullet[i])
				{
					EBullet[i]->TransInfo.Position.x -= 2;

					OnDrawText(EBullet[i]->Info.Texture,
						EBullet[i]->TransInfo.Position.x,
						EBullet[i]->TransInfo.Position.y, 5);
				}
			}
			
			OnDrawText((char*)"Score : ", float( 60 - strlen("Score : ")), 1.0f);
			OnDrawText(++Score, 60.0f, 1.0f);

			OnDrawText((char*)"[                    ]", 1.0f, 28.0f);
		
			
			for (int i = 0; i < Power; ++i)
			{
				OnDrawText((char*)"■", 2.0f + i * 2, 28.0f, 10);
				if ( 7.9f >= Power && Power >= 5.0f )
					OnDrawText((char*)"■", 2.0f + i * 2, 28.0f, 14);

				if ( 9.9f >= Power && Power >= 8.0f )
					OnDrawText((char*)"■", 2.0f + i * 2, 28.0f, 12);				
				if (Power >= 10.0f)
				{
					
					OnDrawText((char*)"[ O V E R H I T !  ! ]", 1.0f, 28.0f, 12);
					OHeat = true;
					if (Err + 5000 < GetTickCount64())
					{
						Err = GetTickCount64();
						OHeat = false;
						Power = 0.0f;
					}
					
				}
			}
			
			
			
		}
	}

	return 0;
}
