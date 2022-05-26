#include "Headers.h"
// v 0.1 «√∑π¿ÃæÓ, ø°≥ πÃ ∏∏µÎ
// v 0.2 ∫Ê∑ø ª˝º∫, ø¿πˆ »˜∆Æ

/*
1. ∆ƒ∂˚
2. ∏≈∆Æ∏ØΩ∫
3. øÏ¡ﬂ√Ê«— «œ¥√
4. ºÆ∑˘
5. ∏∂¡®≈∏
6. ¬§
7. »Úªˆ
8. »∏ªˆ
9. ∆ƒ∂˚
10. ø¨µŒªˆ
11. «œ¥√ªˆ
12. ª°∞≠
13. ∫–»´
14. ≥Î∂˚
15. π‡¿∫ »Úªˆ
*/


int main(void)
{
	HideCursor(false);

	system("mode con:cols=120 lines=60");

	Object* Player = new Object;
	PInitialize(Player, 60.0f, 50.0f);

	Object* Expl = new Object;
	Player->Player.Name = (char*)"∞Ì±Êµø";

	Object* Enemy[64] = { nullptr };
	Object* Bullet[256] = { nullptr };
	Object* Missile[8] = { nullptr };

	ULONGLONG Time = GetTickCount64();
	ULONGLONG EnemyTime = GetTickCount64();
	ULONGLONG ExplTime = GetTickCount64();
	ULONGLONG Cooling = GetTickCount64();
	ULONGLONG ERR = GetTickCount64();
	ULONGLONG Loaded = GetTickCount64();

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
						Enemy[i]->Enemy.Expl = false;

						break;
					}
				}
			}


			// ¿Ãµø
			UpdateInput(Player);

			// Ω∫∆‰¿ÃΩ∫πŸ ∫Ê∑ø
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

			// πÃªÁ¿œ			
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
			
			// «√∑π¿ÃæÓ ∫Ê∑ø ªË¡¶
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
								Enemy[j]->Enemy.Expl = true;

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
			// «√∑π¿ÃæÓ πÃªÁ¿œ ªË¡¶
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
			// «√∑π¿ÃæÓ ∫Ê∑ø ª˝º∫
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

			// πÃªÁ¿œ √‚∑¬
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

			// πÃªÁ¿œ ƒ
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
				if (Enemy[i])
				{
					OnDrawObj(Enemy[i], Enemy[i]->TransInfo.Position.x, Enemy[i]->TransInfo.Position.y);
					if (Enemy[i]->Enemy.Expl = true)
					{
						if (ExplTime - GetTickCount64() < -1999)
							Explosion(Expl, Enemy[i]->TransInfo.Position.x, Enemy[i]->TransInfo.Position.y);
					}
				}
			}
			

			OnDrawText((char*)"SCORE : ", 1.0f, 0.0f);
			OnDrawText((char*)"Heat Gauge : [                    ]", 84.0f, 0.0f);

			OnDrawText((char*)"Missile : ", 101.0f, 1.0f);

			// ø¿πˆ»˜∆Æ
			for (int i = 0; i < Heat; ++i)
			{
				OnDrawText((char*)"°·", 98.0f + i * 2, 0.0f, 10);
				if (7.9f >= Heat && Heat >= 5.0f)
					OnDrawText((char*)"°·", 98.0f + i * 2, 0.0f, 14);

				if (9.9f >= Heat && Heat >= 8.0f)
					OnDrawText((char*)"°·", 98.0f + i * 2, 0.0f, 12);
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