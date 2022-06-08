#include "Headers.h"
// v 0.1 플레이어, 에너미
// v 0.2 뷸렛 생성, 오버 히트
// v 0.3 미사일, 충돌
// v 0.4 HP, 스코어, 배경
// v 0.5 아이템 드랍
// v 0.6 로고, 메인, 점수판
// v 0.7 튜토리얼
// v 0.8 보스 등장까지

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
	PInitialize(Player, 60.0f, 45.0f);
	Player->HP = 5;
	sLogo* logo = new sLogo;

	Object* Enemy1 = new Object;
	EInitialize(Enemy1, 60, 10);
	Enemy1->Enemy.ETime = 1;

	Object* Enemy2 = CreateEnemy(60, 10, 1);
	Object* Enemy3 = CreateEnemy(60, 14, 1);
	Enemy2->Enemy.ETime = 1;
	Enemy3->Enemy.ETime = 1;

	Object* Icon = new Object;
	Initialize(Icon, 20, 52);

	Object* Enemy[64] = { nullptr };
	Object* Ally[6] = { nullptr };
	
	BackGround* BackGround[64] = { nullptr };

	tuto1 = true;
	tuto2 = true;
	tuto3 = true;
	tuto4 = true;
	tuto5 = true;
	tuto6 = true;
	Load = true;

	int ScoreBoard[8] = {  };
	char Initial[8][4] = { };

	while (!Exit)
	{
		// 로고
		if (first)
		{
			LogoScene(logo, Logo, Loading);
			first = false;
		}
		// 메인
		Time = GetTickCount64();
		while (Main)
		{
			if (Time + 50 < GetTickCount64())
			{
				Time = GetTickCount64();
				MainScene(Icon, ScoreBoard, Initial);
				HideCursor(false);
				Story1 = true;
			}			
		}
		tuto1 = true;
		tuto2 = true;
		tuto3 = true;
		tuto4 = true;
		tuto5 = true;
		tuto6 = true; 
		tuto7 = true; 
		Player->Player.Name = (char*)"rrr";
		// 스토리1(튜토리얼)
		/*while (Story1)
		{
			Tutorial(Player, Time, Enemy1, Enemy2, Enemy3);
		}*/
		delete Enemy1;
		delete Enemy2;
		delete Enemy3;
		Heat = 0.0f;
		EnemyTime1 = GetTickCount64();
		Cooling1 = GetTickCount64();
		ERR1 = GetTickCount64();
		Loaded1 = GetTickCount64();
		DropItem1 = GetTickCount64();
		BuffTime1 = GetTickCount64();
		Time = GetTickCount64();
		//R1Time = GetTickCount64();
		R1 = true;
		while (R1 && R1Time + 6000 > GetTickCount64())
		{
			if (Time + 15 < GetTickCount64())
			{
				Time = GetTickCount64();
				system("cls");

				// 배경
				if (BG + 200 < GetTickCount64())
				{
					BG = GetTickCount64();

					for (int i = 0; i < 64; ++i)
					{
						if (BackGround[i] == nullptr)
						{
							srand((GetTickCount64() + i * i) * GetTickCount64());
							BackGround[i] = CreateBackGround(rand());

							break;
						}
					}
				}

				// 에너미 생성
				if (EnemyTime1 + 750 < GetTickCount64())
				{
					EnemyTime1 = GetTickCount64();
					for (int i = 0; i < 64; ++i)
					{
						if (Enemy[i] == nullptr)
						{
							srand((GetTickCount() + i * i) * GetTickCount());
							Enemy[i] = CreateEnemy((rand() % 114 + 2), 6.0f, EnemyTime1);
							Enemy[i]->Enemy.ETime = GetTickCount64();

							break;
						}
					}
				}

				// 에너미 뷸렛 생성
				for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i] != nullptr)
					{
						srand((GetTickCount() + i * i) * GetTickCount());
						if (Enemy[i]->Enemy.ETime + (rand() % 500 + 500) < GetTickCount64())
						{
							Enemy[i]->Enemy.ETime = GetTickCount64();
							for (int j = 0; j < 128; ++j)
							{
								if (EBullet[j] == nullptr)
								{
									EBullet[j] = CreateBullet(
										Enemy[i]->TransInfo.Position.x,
										Enemy[i]->TransInfo.Position.y + 1);

									break;
								}

							}
						}
					}
				}

				// 이동
				if (!Story)
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
							Heat += 0.25f;
						for (int i = 0; i < 128; ++i)
						{
							if (Bullet[i] == nullptr)
							{
								if (!BBuff)
								{
									Bullet[i] = CreateBullet(
										Player->TransInfo.Position.x - 2,
										Player->TransInfo.Position.y + 1);
									Bullet[i + 1] = CreateBullet(
										Player->TransInfo.Position.x + 2,
										Player->TransInfo.Position.y + 1);
								}
								else if (BBuff)
								{
									Bullet[i] = CreateBullet(
										Player->TransInfo.Position.x - 4,
										Player->TransInfo.Position.y + 1);
									Bullet[i + 1] = CreateBullet(
										Player->TransInfo.Position.x + 4,
										Player->TransInfo.Position.y + 1);
									Bullet[i + 2] = CreateBullet(
										Player->TransInfo.Position.x - 2,
										Player->TransInfo.Position.y + 1);
									Bullet[i + 3] = CreateBullet(
										Player->TransInfo.Position.x + 2,
										Player->TransInfo.Position.y + 1);
								}

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
						if (Cooling1 + 500 < GetTickCount64())
						{
							Cooling1 = GetTickCount64();
							if (Heat > 0)
								Heat -= 1.0f;
							if (Heat < 0)
								Heat = 0;
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
								if (!MBuff)
								{
									Missile[i] = CreateBullet(
										Player->TransInfo.Position.x,
										Player->TransInfo.Position.y - 1);
									Missile[i]->Missile.MTime = GetTickCount64();
									Missile[i]->Speed = 0;
									Missile[i]->HP = 3;
								}
								else if (MBuff)
								{
									Missile[i] = CreateBullet(
										Player->TransInfo.Position.x,
										Player->TransInfo.Position.y - 1);
									Missile[i]->Missile.MTime = GetTickCount64();
									Missile[i]->Speed = 0.5;
									Missile[i]->HP = 3;
									Missile[i + 1] = CreateBullet(
										Player->TransInfo.Position.x - 2,
										Player->TransInfo.Position.y - 1);
									Missile[i + 1]->Missile.MTime = GetTickCount64();
									Missile[i + 1]->Speed = 0.5;
									Missile[i + 1]->HP = 3;
									Missile[i + 2] = CreateBullet(
										Player->TransInfo.Position.x + 2,
										Player->TransInfo.Position.y - 1);
									Missile[i + 2]->Missile.MTime = GetTickCount64();
									Missile[i + 2]->Speed = 0.5;
									Missile[i + 2]->HP = 3;
									
								}
								
								Loaded1 = GetTickCount64();
								break;
							}
						}
					}
				}

				// 아이템 생성
				if (DropItem1 + 15000 < GetTickCount64())
				{
					DropItem1 = GetTickCount64();
					for (int i = 0; i < 2; ++i)
					{
						if (Item[i] == nullptr)
						{
							srand((GetTickCount() + i * i) * GetTickCount() + GetTickCount());
							Item[i] = CreateItem(rand());
							break;
						}
					}
				}

				// 플레이어 뷸렛 / 에너미 충돌
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
									ScoreP(500);
									++Kill;
									Score += 500;

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
							if (Bullet[i]->TransInfo.Position.y <= 0)
							{
								delete Bullet[i];
								Bullet[i] = nullptr;
							}
						}
					}
				}

				// 에너미 / 미사일 충돌
				for (int i = 0; i < 8; ++i)
				{
					if (Missile[i] != nullptr)
					{
						for (int j = 0; j < 64; ++j)
						{
							if (Enemy[j] != nullptr)
							{
								if (ECollision(Missile[i], Enemy[j]))
								{
									ScoreP(2000);
									Score += 2000;
									++MKill;

									if (Missile[i]->HP > 1)
									{
										Missile[i]->HP -= 1;
									}

									else if (Missile[i]->HP == 1)
									{
										delete Missile[i];
										Missile[i] = nullptr;
									}


									delete Enemy[j];
									Enemy[j] = nullptr;

									break;
								}
							}
						}
						if (Missile[i] != nullptr)
						{
							if (Missile[i]->TransInfo.Position.y <= 0)
							{
								delete Missile[i];
								Missile[i] = nullptr;
							}
						}

					}
				}

				// 에너미 뷸렛 / 미사일 충돌
				for (int i = 0; i < 128; ++i)
				{
					if (EBullet[i] != nullptr)
					{
						for (int j = 0; j < 8; ++j)
						{
							if (Missile[j] != nullptr)
							{
								if (ECollision(Missile[j], EBullet[i]))
								{
									delete EBullet[i];
									EBullet[i] = nullptr;

									break;
								}
							}
						}
					}

					if (EBullet[i] != nullptr)
					{
						if (PCollision(EBullet[i], Player))
						{
							Player->HP--;

							delete EBullet[i];
							EBullet[i] = nullptr;

							break;
						}
					}

					if (EBullet[i] != nullptr)
					{
						if (EBullet[i]->TransInfo.Position.y >= 60)
						{
							delete EBullet[i];
							EBullet[i] = nullptr;
						}
					}
				}

				// 아이템
				for (int i = 0; i < 2; ++i)
				{
					if (Item[i] != nullptr)
					{
						if (PCollision(Item[i], Player))
						{
							if (Item[i]->Item.Option == 1)
							{
								BuffTime1 = GetTickCount64();
								BBuff = true;
								delete Item[i];
								Item[i] = nullptr;
								break;
							}
							else if (Item[i]->Item.Option == 2)
							{
								if (Player->HP < 5)
									Player->HP++;
								else
								{
									ScoreP(2000);
									Score += 2000;
								}
								delete Item[i];
								Item[i] = nullptr;
								break;
							}
							else if (Item[i]->Item.Option == 3)
							{
								BuffTime1 = GetTickCount64();
								MBuff = true;
								delete Item[i];
								Item[i] = nullptr;
								break;
							}
						}
					}
					if (Item[i] != nullptr)
					{
						if (Item[i]->TransInfo.Position.y >= 59)
						{
							delete Item[i];
							Item[i] = nullptr;
						}
					}
				}

				// Enemy 20 이상일 때 fail
				/*for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i] != nullptr)
					{
						ECount++;
						if (ECount >= 20)
						{
							ECount = 0;
							// 게임 엔드
						}
					}
				}*/
				if (BBuff || MBuff)
				{
					if (BuffTime1 + 10000 < GetTickCount64())
					{
						BBuff = false;
						MBuff = false;
					}
				}
				
				// 배경 출력
				for (int i = 0; i < 64; ++i)
				{
					if (BackGround[i])
					{
						OnDrawBG(BackGround[i]);

						BackGround[i]->TransInfo.Position.y += 1;
						if (BackGround[i]->TransInfo.Position.y >= 60)
						{
							delete BackGround[i];
							BackGround[i] = nullptr;

							break;
						}
					}
				}
				// 플레이어 뷸렛 출력
				for (int i = 0; i < 256; ++i)
				{
					if (Bullet[i])
					{
						OnDrawText(Bullet[i]->Bullet.Texture,
							Bullet[i]->TransInfo.Position.x,
							Bullet[i]->TransInfo.Position.y, 14);

						Bullet[i]->TransInfo.Position.y -= 1.5f;
					}
				}

				// 에너미 뷸렛
				for (int i = 0; i < 128; ++i)
				{
					if (EBullet[i])
					{
						OnDrawText(EBullet[i]->Bullet.Texture,
							EBullet[i]->TransInfo.Position.x,
							EBullet[i]->TransInfo.Position.y, 12);

						EBullet[i]->TransInfo.Position.y += 1.0f;
					}
				}

				// 미사일 출력
				for (int i = 0; i < 8; ++i)
				{
					if (Missile[i])
					{
						OnDrawText(Missile[i]->Missile.Texture[0],
							Missile[i]->TransInfo.Position.x,
							Missile[i]->TransInfo.Position.y, 10);

						if (Missile[i]->Missile.MTime + 500 < GetTickCount64())
						{
							Missile[i]->Missile.MTime = GetTickCount64();
							Missile[i]->Speed += 1.5f;
						}
						Missile[i]->TransInfo.Position.y -= Missile[i]->Speed;
					}
				}

				for (int i = 0; i < 2; ++i)
				{
					if (Item[i])
					{
						OnDrawObj(Item[i], Item[i]->TransInfo.Position.x,
							Item[i]->TransInfo.Position.y);

						Item[i]->TransInfo.Position.y += 0.5f;
					}
				}
				
				// 미사일 쿨
				if (!Load)
				{
					if (Loaded1 - GetTickCount64() >= -999)
						OnDrawText(5, 113.0f, 1.0f, 14);
					else if (Loaded1 - GetTickCount64() >= -1999)
						OnDrawText(4, 113.0f, 1.0f, 14);
					else if (Loaded1 - GetTickCount64() >= -2999)
						OnDrawText(3, 113.0f, 1.0f, 14);
					else if (Loaded1 - GetTickCount64() >= -3999)
						OnDrawText(2, 113.0f, 1.0f, 14);
					else if (Loaded1 - GetTickCount64() >= -4999)
						OnDrawText(1, 113.0f, 1.0f, 14);
					else if (Loaded1 - GetTickCount64() <= -5000 &&
						Loaded1 - GetTickCount64() >= -5049)
						Load = true;
				}
				if (Loaded1 - GetTickCount64() <= -5000)
					OnDrawText((char*)"Loaded", 111.0f, 1.0f, 10);


				OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);

				// 에너미 무빙
				for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i])
					{
						OnDrawObj(Enemy[i], Enemy[i]->TransInfo.Position.x, Enemy[i]->TransInfo.Position.y);
						Direction = GetDirection(Player, Enemy[i]);
						if (Enemy[i]->Enemy.ETime + (rand() % 500 + 500) < GetTickCount64())
						{
							Enemy[i]->Enemy.ETime = GetTickCount64();
							EnemyMove(Enemy[i], Direction, rand() % 5);
						}
					}
				}

				OnDrawText((char*)"SCORE : ", 1.0f, 0.0f);
				OnDrawText(Score, 9.0f, 0.0f, 14);

				OnDrawText((char*)"Missile : ", 101.0f, 1.0f);

				OnDrawText((char*)"Heat Gauge : [                    ]", 84.0f, 0.0f);

				// 오버히트
				for (int i = 0; i < Heat; ++i)
				{
					OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 10);
					if (7.9f >= Heat && Heat >= 5.0f)
					{
						ERR1 = GetTickCount64();
						OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 14);
					}

					if (9.9f >= Heat && Heat >= 8.0f)
					{
						ERR1 = GetTickCount64();
						OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 12);
					}
					if (Heat >= 10.0f)
					{
						OHeat = true;
						OnDrawText((char*)"[ O V E R H E A T ! !]", 97.0f, 0.0f, 12);

						if (ERR1 + 3000 < GetTickCount64())
						{
							ERR1 = GetTickCount64();
							OHeat = false;
							Heat = 0.0f;
						}

					}
				}

				// HP 바
				OnDrawText((char*)"HP : ", 50.0f, 0.0f, 10);
				for (int i = 1; i <= Player->HP; ++i)
				{
					OnDrawText((char*)"♥", 54.0f + i * 2, 0.0f, 10);
					if (Player->HP <= 3)
						OnDrawText((char*)"♥", 54.0f + i * 2, 0.0f, 14);
					if (Player->HP == 1)
						OnDrawText((char*)"♥", 54.0f + i * 2, 0.0f, 12);
					//if (i <= 0)
					// 게임 엔드
				}

				OnDrawText((char*)"남은 시간 : ", 50.0f, 1.0f, 14);
				for (T = 0; T < (R1Time + 60000 - GetTickCount64()) / 1000; ++T)
				{
					if (T >= (R1Time + 60000 - GetTickCount64()) / 1000)
						T = 0;
				}
				OnDrawText(T, 64.0f, 1.0f, 14);								
			}
		}
		for (int i = 0; i < 128; ++i)
		{
			if (EBullet[i] != nullptr)
			{
				delete EBullet[i];
				EBullet[i] != nullptr;
			}
		}
		for (int i = 0; i < 256; ++i)
		{
			if (Bullet[i] != nullptr)
			{
				delete Bullet[i];
				Bullet[i] != nullptr;
			}
		}
		for (int i = 0; i < 8; ++i)
		{
			if (Missile[i] != nullptr)
			{
				delete Missile[i];
				Missile[i] = nullptr;
			}
		}
		for (int i = 0; i < 6; ++i)
		{
			if (Ally[i] == nullptr)
			{
				if (i < 3)
					Ally[i] = CreateAlly(14 + 16 * i, 50.0f, i);
				else if (i >= 3)
					Ally[i] = CreateAlly(26 + 16 * i, 50.0f, i);
			}
		}
		Story2 = true;
		Time = GetTickCount64();
		AllyB = GetTickCount64();
		while (Story2)
		{
			if (Time + 15 < GetTickCount64())
			{				
				Time = GetTickCount64();
				system("cls");
				if (BG + 200 < GetTickCount64())
				{
					BG = GetTickCount64();

					for (int i = 0; i < 64; ++i)
					{
						if (BackGround[i] == nullptr)
						{
							srand((GetTickCount64() + i * i) * GetTickCount64());
							BackGround[i] = CreateBackGround(rand());

							break;
						}
					}
				}
				if (Player->TransInfo.Position.x != 60 || Player->TransInfo.Position.y != 50)
				{
					while (Player->TransInfo.Position.x > 60)
					{
						--Player->TransInfo.Position.x;
						break;
					}									
					while (Player->TransInfo.Position.x < 60)
					{
						++Player->TransInfo.Position.x;
						break;
					}			
					while (Player->TransInfo.Position.y < 50)
					{
						++Player->TransInfo.Position.y;
						break;
					}
					while (Player->TransInfo.Position.y > 50)
					{
						--Player->TransInfo.Position.y;
						break;
					}
				}
					
				
				if (Player->TransInfo.Position.x == 60 && Player->TransInfo.Position.y == 50)
				{
					for (int i = 0; i < 7; i+=6)
					{
						if (AllyB + 150 < GetTickCount64())
						{
							AllyB = GetTickCount64();
							if (Bullet[i] == nullptr && Bullet[i + 1] == nullptr &&
								Bullet[i + 2] == nullptr && Bullet[i + 3] == nullptr &&
								Bullet[i + 4] == nullptr && Bullet[i + 5] == nullptr)
							{
								Bullet[i] = CreateBullet(14, 58);
								Bullet[i + 1] = CreateBullet(30, 58);
								Bullet[i + 2] = CreateBullet(46, 58);
								Bullet[i + 3] = CreateBullet(74, 58);
								Bullet[i + 4] = CreateBullet(90, 58);
								Bullet[i + 5] = CreateBullet(106, 58);
								break;
							}
						}				
					}
				}
				
				for (int i = 0; i < 12; ++i)
				{
					if (Bullet[i] != nullptr)
					{
						if (Bullet[i]->TransInfo.Position.y <= 10)
						{
							for (int j = 0; j < 64; ++j)
							{
								if (Enemy[j] != nullptr)
								{
									delete Enemy[j];
									Enemy[j] = nullptr;
								}
							}
						}
					}
					if (Bullet[i] != nullptr)
					{
						if (Bullet[i]->TransInfo.Position.y <= 2)
						{
							delete Bullet[i];
							Bullet[i] = nullptr;

							break;
						}
					}
				}
				for (int i = 0; i < 64; ++i)
				{
					if (BackGround[i])
					{
						OnDrawBG(BackGround[i]);

						BackGround[i]->TransInfo.Position.y += 1;
						if (BackGround[i]->TransInfo.Position.y >= 60)
						{
							delete BackGround[i];
							BackGround[i] = nullptr;

							break;
						}
					}
				}
				for (int i = 0; i < 12; ++i)
				{
					if (Bullet[i])
					{
						OnDrawText(Bullet[i]->Bullet.Texture, Bullet[i]->TransInfo.Position.x,
							Bullet[i]->TransInfo.Position.y, 14);

						Bullet[i]->TransInfo.Position.y -= 1;
					}
				}
				for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i])
					{
						OnDrawObj(Enemy[i], Enemy[i]->TransInfo.Position.x, Enemy[i]->TransInfo.Position.y);
					}
				}
				if (Enemy[0] == nullptr && Bullet[0] == nullptr)
				{
					Story2 = false;
					Story3 = true;
				}	
				OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
			}
		}
		StoryTime = GetTickCount64();
		while (Story3)
		{
			if (Time + 30 < GetTickCount64())
			{
				Time = GetTickCount64();
				system("cls");

				if (BG + 200 < GetTickCount64())
				{
					BG = GetTickCount64();

					for (int i = 0; i < 64; ++i)
					{
						if (BackGround[i] == nullptr)
						{
							srand((GetTickCount64() + i * i) * GetTickCount64());
							BackGround[i] = CreateBackGround(rand());

							break;
						}
					}
				}
				
				for (int i = 0; i < 12; ++i)
				{
					if (Bullet[i] != nullptr)
					{
						if (Bullet[i]->TransInfo.Position.y <= 4)
						{
							delete Bullet[i];
							Bullet[i] = nullptr;

							break;
						}
					}
				}
				if (StoryTime + 5000 < GetTickCount64() && Ally[0] != nullptr)
				{
					for (int i = 0; i < 6; ++i)
					{
						if (EMissile[i] == nullptr)
						{
							if (i < 3)
							{
								EMissile[i] = CreateBullet(14 + 16 * i, 0);
								EMissile[i]->Speed = 3;
							}
							if (i >= 3)
							{
								EMissile[i] = CreateBullet(26 + 16 * i, 0);
								EMissile[i]->Speed = 3;
							}
						}
						
					}
				}
				for (int i = 0; i < 8; ++i)
				{
					if (EMissile[i] != nullptr)
					{
						for (int j = 0; j < 6; ++j)
						{
							if (Ally[j] != nullptr)
							{
								if (EMissile[i]->TransInfo.Position.y >= 49)
								{
									delete EMissile[i];
									EMissile[i] = nullptr;

									delete Ally[j];
									Ally[j] = nullptr;

									break;
								}
							}
						}
					}
				}
				for (int i = 0; i < 64; ++i)
				{
					if (BackGround[i])
					{
						OnDrawBG(BackGround[i]);

						BackGround[i]->TransInfo.Position.y += 1;
						if (BackGround[i]->TransInfo.Position.y >= 60)
						{
							delete BackGround[i];
							BackGround[i] = nullptr;

							break;
						}
					}
				}
				for (int i = 0; i < 8; ++i)
				{
					if (EMissile[i])
					{
						OnDrawText(EMissile[i]->Missile.Texture[1], EMissile[i]->TransInfo.Position.x, EMissile[i]->TransInfo.Position.y, 12);
						EMissile[i]->TransInfo.Position.y += EMissile[i]->Speed;
					}
				}
				for (int i = 0; i < 6; ++i)
				{
					if (Ally[i])
						OnDrawObj(Ally[i], Ally[i]->TransInfo.Position.x, Ally[i]->TransInfo.Position.y);
				}
				for (int i = 0; i < 6; ++i)
				{
					if (Bullet[i])
					{
						OnDrawText(Bullet[i]->Bullet.Texture, Bullet[i]->TransInfo.Position.x,
							Bullet[i]->TransInfo.Position.y, 14);

						Bullet[i]->TransInfo.Position.y -= 1;
					}
				}
				for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i])
						OnDrawObj(Enemy[i], Enemy[i]->TransInfo.Position.x, Enemy[i]->TransInfo.Position.y);
					
				}
				OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
				if (StoryTime + 2500 < GetTickCount64() && StoryTime + 3000 > GetTickCount64())
				{
					for (int i = 0; i < 6; ++i)
					{
						if (i < 3)
							Warning(14 + 16 * i, 0);
						if (i >= 3)
							Warning(26 + 16 * i, 0);
					}				
				}
				if (StoryTime + 3500 < GetTickCount64() && StoryTime + 4000 > GetTickCount64())
				{
					for (int i = 0; i < 6; ++i)
					{
						if (i < 3)
							Warning(15 + 16 * i, 0);
						if (i >= 3)
							Warning(26 + 16 * i, 0);
					}				
				}
				if ((StoryTime + 1000 < GetTickCount64() && StoryTime + 2600 > GetTickCount64()) || (StoryTime + 4000 < GetTickCount64() && StoryTime + 5000 > GetTickCount64()))
				{
					OnDrawText((char*)"┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒", 60 - strlen("┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒") / 2, 24);
					OnDrawText((char*)"ㅣ                             ㅣ", 60 - strlen("┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒") / 2, 25);
					OnDrawText((char*)"ㅣ                             ㅣ", 60 - strlen("┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒") / 2, 26);
					OnDrawText((char*)"ㅣ                             ㅣ", 60 - strlen("┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒") / 2, 27);
					OnDrawText((char*)"┖ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┚", 60 - strlen("┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒") / 2, 28);
				}
				if (StoryTime + 1000 < GetTickCount64() && StoryTime + 2500 > GetTickCount64())
				{					
					OnDrawText((char*)"살았다..! 지원이 왔어", 60 - strlen("살았다..! 지원이 왔어") / 2, 26);
				}
				if (StoryTime + 4000 < GetTickCount64() && StoryTime + 5000 > GetTickCount64())
				{
					OnDrawText((char*)"...!!!   위험해!!", 60 - strlen("...!!!   위험해!!") / 2, 26);
				}
				if ((StoryTime + 6500 < GetTickCount64() && StoryTime + 7400 > GetTickCount64()) || (StoryTime + 8500 < GetTickCount64() && StoryTime + 9400 > GetTickCount64()))
					Warning2(23);
				if (StoryTime + 9500 < GetTickCount64())
				{
					Story3 = false;
					Story4 = true;
				}
			}
			
		}
		Heat = 0.0f;
		EnemyTime1 = GetTickCount64();
		Cooling1 = GetTickCount64();
		ERR1 = GetTickCount64();
		Loaded1 = GetTickCount64();
		DropItem1 = GetTickCount64();
		BuffTime1 = GetTickCount64();
		Time = GetTickCount64();
		while (Story4)
		{
			if (Time + 15 < GetTickCount64())
			{
				Time = GetTickCount64();
				system("cls");

				if (BG + 200 < GetTickCount64())
				{
					BG = GetTickCount64();

					for (int i = 0; i < 64; ++i)
					{
						if (BackGround[i] == nullptr)
						{
							srand((GetTickCount64() + i * i) * GetTickCount64());
							BackGround[i] = CreateBackGround(rand());

							break;
						}
					}
				}
				for (int i = 0; i < 64; ++i)
				{
					if (BackGround[i])
					{
						OnDrawBG(BackGround[i]);

						BackGround[i]->TransInfo.Position.y += 1;
						if (BackGround[i]->TransInfo.Position.y >= 60)
						{
							delete BackGround[i];
							BackGround[i] = nullptr;

							break;
						}
					}
				}
				OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
			}
			BossScene();
		}
	}
		
	return 0;
}