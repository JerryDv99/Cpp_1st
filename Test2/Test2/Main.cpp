#include "Headers.h"
// v 0.1 플레이어, 에너미 만듬
// v 0.2 뷸렛 생성, 오버 히트

/*
1. 파랑
2. 매트릭스
3. 우중충한 하늘
4. 석류
5. 마젠타
6. 짚
7. 흰색
8. 회색
9. 파랑
10. 연두색
11. 하늘색
12. 빨강
13. 분홍
14. 노랑
15. 밝은 흰색
*/


int main(void)
{
	HideCursor(false);

	system("mode con:cols=120 lines=60");

	Object* Player = new Object;
	PInitialize(Player, 60.0f, 50.0f);

	Player->Player.Name = (char*)"고길동";

	Object* Enemy[64] = { nullptr };
	Object* Bullet[256] = { nullptr };
	Object* Missile[8] = { nullptr };

	ULONGLONG Time = GetTickCount64();
	ULONGLONG EnemyTime = GetTickCount64();
	ULONGLONG Cooling = GetTickCount64();
	ULONGLONG ERR = GetTickCount64();
	ULONGLONG Loaded = GetTickCount64();

	int Score = 0;

	bool Check = false;
	bool OHeat = false;
	bool Load = false;

	float Heat = 0.2f;

	while (true)
	{
		if (Time + 500 < GetTickCount64())
		{
			system("cls");

			if (EnemyTime + 1000 < GetTickCount64())
			{
				EnemyTime = GetTickCount64();
				for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i] == nullptr)
					{
						srand((GetTickCount() + i * i) * GetTickCount());
						Enemy[i] = CreateEnemy((rand() % 116 + 2), 6.0f, EnemyTime);
						Enemy[i]->Enemy.ETime = GetTickCount64();

						break;
					}
				}
			}

			// 이동
			UpdateInput(Player);

			// 스페이스바 뷸렛
			if (!OHeat)
			{
				if (!Check && GetAsyncKeyState(VK_SPACE) & 0x0001)
				{
					Check = true;
				}
				if (GetAsyncKeyState(VK_SPACE) & 0x8000)
				{
					if (Heat < 10)
						Heat += 0.1f;
					for (int i = 0; i < 128; ++i)
					{
						if (Bullet[i] == nullptr)
						{
							Bullet[i] = CreateBullet(
								Player->TransInfo.Position.x - 2,
								Player->TransInfo.Position.y + 1);
							Bullet[i + 1] = CreateBullet(
								Player->TransInfo.Position.x + 2,
								Player->TransInfo.Position.y + 1);

							break;							
						}
					}					
				}
				if (Check && !(GetAsyncKeyState(VK_SPACE) & 0x8000))
				{
					Check = false;
				}
				if (!Check)
				{
					if (Cooling + 500 < GetTickCount64())
					{
						Cooling = GetTickCount64();
						if(Heat > 0)
							Heat -= 1.0f;
					}
				}
			}

			// 미사일			
			if (Load)
			{
				if (GetAsyncKeyState(0x58))
				{
					for (int i = 0; i < 8; ++i)
					{
						if (Missile[i] == nullptr)
						{
							Load = false;
							Missile[i] = CreateBullet(
								Player->TransInfo.Position.x,
								Player->TransInfo.Position.y - 1);
							Missile[i]->Missile.MTime = GetTickCount64();
							Missile[i]->Speed = 0;
							Loaded = GetTickCount64();
							break;
						}
					}
				}
			}
			
			// 플레이어 뷸렛 삭제
			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i] != nullptr)
				{
					for (int j = 0; j < 64; ++j)
					{
						if (Enemy[j] != nullptr)
						{
							if (ECollision(Bullet[i], Enemy[j]))
							{
								ScorePP(500);
								Score += 500;
								delete Bullet[i];
								Bullet[i] = nullptr;

								delete Enemy[j];
								Enemy[j] = nullptr;

								break;																					
							}
						}
					}
					if (Bullet[i] != nullptr)
					{
						if (Bullet[i]->TransInfo.Position.y <= 0)
						{
							delete Bullet[i];
							Bullet[i] = nullptr;
						}
					}					
				}
			}
			// 플레이어 미사일 삭제
			for (int i = 0; i < 8; ++i)
			{
				if (Missile[i] != nullptr)
				{
					if (Missile[i]->TransInfo.Position.y <= 0)
					{
						delete Missile[i];
						Missile[i] = nullptr;
					}
				}
			}
			// 플레이어 뷸렛 생성
			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i])
				{
					OnDrawText(Bullet[i]->Bullet.Texture,
						Bullet[i]->TransInfo.Position.x,
						Bullet[i]->TransInfo.Position.y, 14);	

					Bullet[i]->TransInfo.Position.y -= 1.5f;
				}
			}

			// 미사일 출력
			for (int i = 0; i < 8; ++i)
			{
				if (Missile[i])
				{
					OnDrawText(Missile[i]->Missile.Texture,
						Missile[i]->TransInfo.Position.x,
						Missile[i]->TransInfo.Position.y, 10);	
					
					if (Missile[i]->Missile.MTime + 500 < GetTickCount64())
					{
						Missile[i]->Missile.MTime = GetTickCount64();
						Missile[i]->Speed += 1;
					}
					Missile[i]->TransInfo.Position.y -= Missile[i]->Speed;
				}				
			}

			// 미사일 쿨
			if (!Load)
			{
				if (Loaded - GetTickCount64() >= - 999)
					OnDrawText(5, 113.0f, 1.0f, 14);
				else if (Loaded - GetTickCount64() >= - 1999)
					OnDrawText(4, 113.0f, 1.0f, 14);
				else if (Loaded - GetTickCount64() >= - 2999)
					OnDrawText(3, 113.0f, 1.0f, 14);
				else if (Loaded - GetTickCount64() >= - 3999)
					OnDrawText(2, 113.0f, 1.0f, 14);
				else if (Loaded - GetTickCount64() >= - 4999)
					OnDrawText(1, 113.0f, 1.0f, 14);
				else if (Loaded - GetTickCount64() == - 5000)
					Load = true;			
			}
			if (Loaded - GetTickCount64() <= -5000)
				OnDrawText((char*)"Loaded", 111.0f, 1.0f, 10);

			OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);

			for (int i = 0; i < 64; ++i)
			{
				float x = 0;
				float y = 0;
				if (Enemy[i])
				{
					x = Enemy[i]->TransInfo.Position.x;
					y = Enemy[i]->TransInfo.Position.y;
					OnDrawObj(Enemy[i], Enemy[i]->TransInfo.Position.x, Enemy[i]->TransInfo.Position.y);
					
				}
			}
			

			OnDrawText((char*)"SCORE : ", 1.0f, 0.0f);
			OnDrawText(Score, 9.0f, 0.0f);
			OnDrawText((char*)"Heat Gauge : [                    ]", 84.0f, 0.0f);

			OnDrawText((char*)"Missile : ", 101.0f, 1.0f);

			// 오버히트
			for (int i = 0; i < Heat; ++i)
			{
				OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 10);
				if (7.9f >= Heat && Heat >= 5.0f)
					OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 14);

				if (9.9f >= Heat && Heat >= 8.0f)
					OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 12);
				if (Heat >= 10.0f)
				{
					OHeat = true;
					OnDrawText((char*)"[ O V E R H E A T ! !]", 97.0f, 0.0f, 12);
					
					if (ERR + 5000 < GetTickCount64())
					{
						ERR = GetTickCount64();
						OHeat = false;
						Heat = 0.0f;
					}

				}
			}
			

		}
		
	}


	return 0;
}