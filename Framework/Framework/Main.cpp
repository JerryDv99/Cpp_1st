// Framework v 0.3
// 플레이어 몬스터 씬관리 투사체 충돌

// Bullet이 몬스터와 충돌 시 Bullet 제거
#include "Headers.h"

int main(void)
{

	HideCursor(false); // 커서를 숨김

	// 배경 초기화
	
	DrawTextInfo BackGround[30];


	for (int i = 0; i < 30; ++i)
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

	int Score = 0;

	Object* Bullet[128] = { nullptr };
	Object* EBullet[128] = { nullptr };

	Object* Temp = new Object;

	Temp->TransInfo.Position.y = 10;
	Temp->TransInfo.Position.x = 80;

	Temp->Info.Texture = (char*)"-=";

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
			for (int i = 0; i < 30; ++i)
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
			if (EnemyTime + 1500 < GetTickCount64())
			{
				EnemyTime = GetTickCount64();
				for (int i = 0; i < 32; ++i)
				{
					if (Enemy[i] == nullptr)
					{
						srand((GetTickCount() + i * i) * GetTickCount());
						Enemy[i] = CreateEnemy(115, rand()%30);

						break;
					}
				}
				// ** 수정할거
				int EnemyTime2 = 0;
				int mcount = 0;
				if (EnemyTime2 + 500 < GetTickCount64())
				{
					EnemyTime2 = GetTickCount64();
					for (int i = 0; i < 32; ++i)
					{
						if (EBullet[mcount] == nullptr)
						{
							EBullet[mcount] = CreateBullet(
								Enemy[i]->TransInfo.Position.x - 2,
								Enemy[i]->TransInfo.Position.y);
							mcount++;
							if (mcount >= 127)
								mcount = 0;

							break;
						}
					}
				}

			}

			for (int i = 0; i < 128; ++i)
			{
				if (EBullet[i] != nullptr)
				{
					for (int j = 0; j < 32; ++j)
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


			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i] != nullptr)
				{
					for (int j = 0; j < 32; ++j)
					{
						if (Enemy[j] != nullptr)
						{
							if (Collision(Enemy[j], Bullet[i]))
							{
								delete Enemy[j];
								Enemy[j] = nullptr;

								delete Bullet[i];
								Bullet[i] = nullptr;
								break;
							}
						}
					}
					if (Bullet[i] != nullptr)
					{
						if (Bullet[i]->TransInfo.Position.x + Bullet[i]->TransInfo.Scale.x >= 120)
						{
							delete Bullet[i];
							Bullet[i] = nullptr;	// 반복문 안에서 delete는 위험
						}
					}
				}
			}
			
			//if (Collision(Player, Enemy))
				//OnDrawText((char*)"충돌 입니다.", Enemy->TransInfo.Position.x, Enemy->TransInfo.Position.y - 1, 12);
		
			UpdateInput(Player);

			// 스페이스 키를 입력받음
			if (GetAsyncKeyState(VK_SPACE))
			{
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

			// Player 출력
			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);
			
			OnDrawText(Temp->Info.Texture,
				Temp->TransInfo.Position.x,
				Temp->TransInfo.Position.y,
				12);

			// 3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333

			float x = Player->TransInfo.Position.x - Temp->TransInfo.Position.x;
			float y = Player->TransInfo.Position.y - Temp->TransInfo.Position.y;


			// sqrt : 제곱근 함수
			float Length = sqrt((x * x) + (y * y));

			Vector3 Direction = Vector3(x / Length, y / Length);

			Temp->TransInfo.Position.x += Direction.x;
			Temp->TransInfo.Position.y += Direction.y;

			OnDrawText((char*)"Length : ", float(60 - strlen("Length : ")), 2.0f);
			OnDrawText((int)Length, 60.0f, 2.0f);


		
			




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
				if (EBullet[i] != nullptr)
				{
					EBullet[i]->TransInfo.Position.x -= 2;

					OnDrawText(EBullet[i]->Info.Texture,
						EBullet[i]->TransInfo.Position.x,
						EBullet[i]->TransInfo.Position.y);
				}
			}
			
			OnDrawText((char*)"Score : ", float( 60 - strlen("Score : ")), 1.0f);
			OnDrawText(++Score, 60.0f, 1.0f);


		}
	}

	return 0;
}
