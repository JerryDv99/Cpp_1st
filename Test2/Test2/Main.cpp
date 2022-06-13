#include "Headers.h"
// v 0.1 플레이어, 에너미
// v 0.2 뷸렛 생성, 오버 히트
// v 0.3 미사일, 충돌
// v 0.4 HP, 스코어, 배경
// v 0.5 아이템 드랍
// v 0.6 로고, 메인, 점수판
// v 0.7 튜토리얼
// v 0.8 보스 등장씬, 도우미
// v 0.9 보스전
// 
// 
// 만들거 : fail / 재도전 씬, 다 깨면 점수 계산, 받아서 점수표에 올리는거, 보스전, 튜토리얼 선택
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
	
	BOSS* Boss = new BOSS;

	HB[0] = new Hitbox;
	HInitialize(HB[0], 8, 4);
	HB[1] = new Hitbox;
	HInitialize(HB[1], 20, 6);
	HB[2] = new Hitbox;
	HInitialize(HB[2], 29, 7);
	HB[3] = new Hitbox;
	HInitialize(HB[3], 41, 7);
	HB[4] = new Hitbox;
	HInitialize(HB[4], 75, 7);
	HB[5] = new Hitbox;
	HInitialize(HB[5], 87, 7);
	HB[6] = new Hitbox;
	HInitialize(HB[6], 96, 6);
	HB[7] = new Hitbox;
	HInitialize(HB[7], 108, 4);



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
		Life = 2;
		Heat = 0;
		Score = 0;
		HCount = 0;
		ECount = 0;
		Kill = 0;
		MKill = 0;
		Main = true;
		PSA = false;
		BSA = false;
		UI = true;
		E1V = false;
		E2V = false;
		E3V = false;

		R1 = false;
		RCheck = false;
		LCheck = false;
		ECheck = false;
		first = true;
		Story1 = false;
		Story2 = false;
		Story3 = false;
		Story4 = false;
		Story = false;
		Check = false;
		OHeat = false;
		Load = false;
		BBuff = false;
		MBuff = false;
		Exit = false;
		Player->HP = 5;
		Player->TransInfo.Position.x = 60;
		Player->TransInfo.Position.y = 45;
		Player->Player.Name = nullptr;
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

		// 스토리1(튜토리얼)
		while (Story1)
		{
			Tutorial(Player, Time, Enemy1, Enemy2, Enemy3);
			if (GetAsyncKeyState(VK_TAB) && Player->Player.Name != nullptr)
				break;
		}
		Heat = 0.0f;
		EnemyTime = GetTickCount64();
		Cooling = GetTickCount64();
		ERR = GetTickCount64();
		Loaded = GetTickCount64();
		DropItem = GetTickCount64();
		BuffTime = GetTickCount64();
		Time = GetTickCount64();
		R1Time = GetTickCount64();
		Load = false;
		R1 = true;
		while (R1 && R1Time + 6000 > GetTickCount64())
		{
			if (Time + 20 < GetTickCount64())
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
				if (EnemyTime + 1000 < GetTickCount64())
				{
					EnemyTime = GetTickCount64();
					for (int i = 0; i < 64; ++i)
					{
						if (Enemy[i] == nullptr)
						{
							srand((GetTickCount() + i * i) * GetTickCount());
							Enemy[i] = CreateEnemy((rand() % 114 + 2), 6.0f, EnemyTime);
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
						if (Cooling + 500 < GetTickCount64())
						{
							Cooling = GetTickCount64();
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
								
								Loaded = GetTickCount64();
								break;
							}
						}
					}
				}

				// 아이템 생성
				if (DropItem + 15000 < GetTickCount64())
				{
					DropItem = GetTickCount64();
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
							if (Bullet[i]->TransInfo.Position.y <= 4)
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
							if (Missile[i]->TransInfo.Position.y <= 4)
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
						if (!PSA)
						{
							if (PCollision(EBullet[i], Player))
							{
								Player->HP--;
								HCount++;
								PSA = true;
								SpArmorP = GetTickCount64();

								delete EBullet[i];
								EBullet[i] = nullptr;

								break;
							}
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
								BuffTime = GetTickCount64();
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
								BuffTime = GetTickCount64();
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
					if (BuffTime + 10000 < GetTickCount64())
					{
						BBuff = false;
						MBuff = false;
					}
				}
				if (SpArmorP + 1500 < GetTickCount64())
					PSA = false;

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
					if (Loaded - GetTickCount64() >= -999)
						OnDrawText(5, 113.0f, 1.0f, 14);
					else if (Loaded - GetTickCount64() >= -1999)
						OnDrawText(4, 113.0f, 1.0f, 14);
					else if (Loaded - GetTickCount64() >= -2999)
						OnDrawText(3, 113.0f, 1.0f, 14);
					else if (Loaded - GetTickCount64() >= -3999)
						OnDrawText(2, 113.0f, 1.0f, 14);
					else if (Loaded - GetTickCount64() >= -4999)
						OnDrawText(1, 113.0f, 1.0f, 14);
					else if (Loaded - GetTickCount64() <= -5000 &&
						Loaded - GetTickCount64() >= -5049)
						Load = true;
				}
				if (Loaded - GetTickCount64() <= -5000)
					OnDrawText((char*)"Loaded", 111.0f, 1.0f, 10);

				if (!PSA)
					OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
				else if (PSA)
				{
					if (SpArmorP + 250 < GetTickCount64() && SpArmorP + 499 > GetTickCount64())
						OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
					if (SpArmorP + 750 < GetTickCount64() && SpArmorP + 999 > GetTickCount64())
						OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
					if (SpArmorP + 1250 < GetTickCount64() && SpArmorP + 1499 > GetTickCount64())
						OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
				}

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
							EnemyMove(Enemy[i], Direction, rand() % 5, 1);
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
						ERR = GetTickCount64();
						OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 14);
					}

					if (9.9f >= Heat && Heat >= 8.0f)
					{
						ERR = GetTickCount64();
						OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 12);
					}
					if (Heat >= 10.0f)
					{
						OHeat = true;
						OnDrawText((char*)"[ O V E R H E A T ! !]", 97.0f, 0.0f, 12);

						if (ERR + 3000 < GetTickCount64())
						{
							ERR = GetTickCount64();
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
				EBullet[i] = nullptr;
			}
		}
		for (int i = 0; i < 256; ++i)
		{
			if (Bullet[i] != nullptr)
			{
				delete Bullet[i];
				Bullet[i] = nullptr;
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
				for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i])
					{
						ECheck = true;
						break;
					}
					else if (Enemy[i] == nullptr)
						ECheck = false;
				}
				if (Player->TransInfo.Position.x == 60 && Player->TransInfo.Position.y == 50 && !ECheck)
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
		
		StoryTime = GetTickCount64();
		while (Story4)
		{
			if (Time + 20 < GetTickCount64())
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
				if((StoryTime + 0 < GetTickCount64()) && (StoryTime + 99 > GetTickCount64()))
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 0, 6);
				if ((StoryTime + 100 < GetTickCount64()) && (StoryTime + 199 > GetTickCount64()))														
				{																																		
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 0, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 1, 6);
				}
				if ((StoryTime + 200 < GetTickCount64()) && (StoryTime + 299 > GetTickCount64()))
				{
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 0, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 1, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 2, 6);
				}							
				if ((StoryTime + 300 < GetTickCount64()) && (StoryTime + 399 > GetTickCount64()))
				{
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 0, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 1, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 2, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 3, 6);
				}
				if ((StoryTime + 400 < GetTickCount64()) && (StoryTime + 499 > GetTickCount64()))
				{
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 0, 6);
					OnDrawText((char*)"**", 59, 0, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 1, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 2, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 3, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 4, 6);
				}
				if ((StoryTime + 500 < GetTickCount64()) && (StoryTime + 599 > GetTickCount64()))
				{
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 0, 6);
					OnDrawText((char*)"****", 58, 0, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 1, 6);
					OnDrawText((char*)"**", 59, 1, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 2, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 3, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 4, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 5, 6);
				}				
				if ((StoryTime + 600 < GetTickCount64()) && (StoryTime + 699 > GetTickCount64()))
				{
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 0, 6);
					OnDrawText((char*)"**::**", 57, 0, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 1, 6);
					OnDrawText((char*)"****", 58, 1, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 2, 6);
					OnDrawText((char*)"**", 59, 2, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 3, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 4, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 5, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 6, 6);
				}
				if ((StoryTime + 700 < GetTickCount64()) && (StoryTime + 799 > GetTickCount64()))
				{
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 0, 6);
					OnDrawText((char*)"***", 56, 0, 12);
					OnDrawText((char*)"***", 62, 0, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 1, 6);
					OnDrawText((char*)"**::**", 57, 1, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 2, 6);
					OnDrawText((char*)"****", 58, 2, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 3, 6);
					OnDrawText((char*)"**", 59, 3, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 4, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 5, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 6, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 7, 6);
				}
				if ((StoryTime + 800 < GetTickCount64()) && (StoryTime + 899 > GetTickCount64()))
				{
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 0, 6);
					OnDrawText((char*)"***", 55, 0, 12);
					OnDrawText((char*)"***", 62, 0, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 1, 6);
					OnDrawText((char*)"***", 56, 1, 12);
					OnDrawText((char*)"***", 61, 1, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 2, 6);
					OnDrawText((char*)"**::**", 57, 2, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 3, 6);
					OnDrawText((char*)"****", 58, 3, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 4, 6);
					OnDrawText((char*)"**", 59, 4, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 5, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 6, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 7, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 8, 6);
				}
				if ((StoryTime + 900 < GetTickCount64()) && (StoryTime + 999 > GetTickCount64()))
				{
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 0, 6);
					OnDrawText((char*)"***", 54, 0, 12);
					OnDrawText((char*)"***", 63, 0, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 1, 6);
					OnDrawText((char*)"***", 55, 1, 12);
					OnDrawText((char*)"***", 62, 1, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 2, 6);
					OnDrawText((char*)"***", 56, 2, 12);
					OnDrawText((char*)"***", 61, 2, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 3, 6);
					OnDrawText((char*)"**::**", 57, 3, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 4, 6);
					OnDrawText((char*)"****", 58, 4, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 5, 6);
					OnDrawText((char*)"**", 59, 5, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 6, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 7, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 8, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 9, 6);
				}
				if ((StoryTime + 1000 < GetTickCount64()) && (StoryTime + 1099 > GetTickCount64()))
				{
					OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", 5, 0, 6);
					OnDrawText((char*)"**", 54, 0, 12);
					OnDrawText((char*)"**", 64, 0, 12);
					OnDrawText((char*)"VV", 24, 0, 13);
					OnDrawText((char*)"VV", 36, 0, 13);
					OnDrawText((char*)"VV", 94, 0, 13);
					OnDrawText((char*)"VV", 82, 0, 13);
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 1, 6);
					OnDrawText((char*)"***", 54, 1, 12);
					OnDrawText((char*)"***", 63, 1, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 2, 6);
					OnDrawText((char*)"***", 55, 2, 12);
					OnDrawText((char*)"***", 62, 2, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 3, 6);
					OnDrawText((char*)"***", 56, 3, 12);
					OnDrawText((char*)"***", 61, 3, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 4, 6);
					OnDrawText((char*)"**::**", 57, 4, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 5, 6);
					OnDrawText((char*)"****", 58, 5, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 6, 6);
					OnDrawText((char*)"**", 59, 6, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 7, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 8, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 9, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 10, 6);
				}
				if ((StoryTime + 1100 < GetTickCount64()) && (StoryTime + 1199 > GetTickCount64()))
				{
					OnDrawText((char*)"                LNNFNNMFIIIIUUBUUFUUVVVUUUVFVVVVFFVVV****VIFFVVVFIMIUUUVUVUUUUU*VMIIIIUFUUUN/                 ", 5, 0, 6);
					OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", 5, 1, 6);
					OnDrawText((char*)"**", 54, 1, 12);
					OnDrawText((char*)"**", 64, 1, 12);
					OnDrawText((char*)"VV", 24, 1, 13);
					OnDrawText((char*)"VV", 36, 1, 13);
					OnDrawText((char*)"VV", 82, 1, 13);
					OnDrawText((char*)"VV", 94, 1, 13);
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 2, 6);
					OnDrawText((char*)"***", 54, 2, 12);
					OnDrawText((char*)"***", 63, 2, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 3, 6);
					OnDrawText((char*)"***", 55, 3, 12);
					OnDrawText((char*)"***", 62, 3, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 4, 6);
					OnDrawText((char*)"***", 56, 4, 12);
					OnDrawText((char*)"***", 61, 4, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 5, 6);
					OnDrawText((char*)"**::**", 57, 5, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 6, 6);
					OnDrawText((char*)"****", 58, 6, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 7, 6);
					OnDrawText((char*)"**", 59, 7, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 8, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 9, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 10, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 11, 6);
				}
				if ((StoryTime + 1200 < GetTickCount64()) && (StoryTime + 1299 > GetTickCount64()))
				{
					OnDrawText((char*)"              NNNM*VVVVVVV*NNNVVFVVFFF**BNFFVVFFFVVV******IFVVIVFIII**VV*NFVVFF*VVVVFVVVVV:MNNNN              ", 5, 0, 6);
					OnDrawText((char*)"VV", 15, 0, 13);
					OnDrawText((char*)"VV", 103, 0, 13);
					OnDrawText((char*)"                LNNFNNMFIIIIUUBUUFUUVVVUUUVFVVVVFFVVV****VIFFVVVFIMIUUUVUVUUUUU*VMIIIIUFUUUN/                 ", 5, 1, 6);
					OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", 5, 2, 6);
					OnDrawText((char*)"**", 54, 2, 12);
					OnDrawText((char*)"**", 64, 2, 12);
					OnDrawText((char*)"VV", 24, 2, 13);
					OnDrawText((char*)"VV", 36, 2, 13);
					OnDrawText((char*)"VV", 82, 2, 13);
					OnDrawText((char*)"VV", 94, 2, 13);
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 3, 6);
					OnDrawText((char*)"***", 54, 3, 12);
					OnDrawText((char*)"***", 63, 3, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 4, 6);
					OnDrawText((char*)"***", 55, 4, 12);
					OnDrawText((char*)"***", 62, 4, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 5, 6);
					OnDrawText((char*)"***", 56, 5, 12);
					OnDrawText((char*)"***", 61, 5, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 6, 6);
					OnDrawText((char*)"**::**", 57, 6, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 7, 6);
					OnDrawText((char*)"****", 58, 7, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 8, 6);
					OnDrawText((char*)"**", 59, 8, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 9, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 10, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 11, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 12, 6);
				}
				if ((StoryTime + 1300 < GetTickCount64()) && (StoryTime + 1399 > GetTickCount64()))
				{
					OnDrawText((char*)"        NMMMFVVVV***::******************IVIVVVFVFVV********IVVVVVIIM:.*V*******V*********VVVFIIIMMMNNN        ", 5, 0, 6);
					OnDrawText((char*)"              NNNM*VVVVVVV*NNNVVFVVFFF**BNFFVVFFFVVV******IFVVIVFIII**VV*NFVVFF*VVVVFVVVVV:MNNNN              ", 5, 1, 6);
					OnDrawText((char*)"VV", 15, 1, 13);
					OnDrawText((char*)"VV", 103, 1, 13);
					OnDrawText((char*)"                LNNFNNMFIIIIUUBUUFUUVVVUUUVFVVVVFFVVV****VIFFVVVFIMIUUUVUVUUUUU*VMIIIIUFUUUN/                 ", 5, 2, 6);
					OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", 5, 3, 6);
					OnDrawText((char*)"**", 54, 3, 12);
					OnDrawText((char*)"**", 64, 3, 12);
					OnDrawText((char*)"VV", 24, 3, 13);
					OnDrawText((char*)"VV", 36, 3, 13);
					OnDrawText((char*)"VV", 82, 3, 13);
					OnDrawText((char*)"VV", 94, 3, 13);
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 4, 6);
					OnDrawText((char*)"***", 54, 4, 12);
					OnDrawText((char*)"***", 63, 4, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 5, 6);
					OnDrawText((char*)"***", 55, 5, 12);
					OnDrawText((char*)"***", 62, 5, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 6, 6);
					OnDrawText((char*)"***", 56, 6, 12);
					OnDrawText((char*)"***", 61, 6, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 7, 6);
					OnDrawText((char*)"**::**", 57, 7, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 8, 6);
					OnDrawText((char*)"****", 58, 8, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 9, 6);
					OnDrawText((char*)"**", 59, 9, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 10, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 11, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 12, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 13, 6);
				}
				if ((StoryTime + 1400 < GetTickCount64()) && (StoryTime + 1499 > GetTickCount64()))
				{
					OnDrawText((char*)"      NN************:******V**:::*******IIVVVVIIIV**********VVVVVIIV********:::*VVV**************VVFFIIM      ", 5, 0, 6);
					OnDrawText((char*)"VV", 7, 0, 13);
					OnDrawText((char*)"VV", 111, 0, 13);
					OnDrawText((char*)"        NMMMFVVVV***::******************IVIVVVFVFVV********IVVVVVIIM:.*V*******V*********VVVFIIIMMMNNN        ", 5, 1, 6);
					OnDrawText((char*)"              NNNM*VVVVVVV*NNNVVFVVFFF**BNFFVVFFFVVV******IFVVIVFIII**VV*NFVVFF*VVVVFVVVVV:MNNNN              ", 5, 2, 6);
					OnDrawText((char*)"VV", 15, 2, 13);
					OnDrawText((char*)"VV", 103, 2, 13);
					OnDrawText((char*)"                LNNFNNMFIIIIUUBUUFUUVVVUUUVFVVVVFFVVV****VIFFVVVFIMIUUUVUVUUUUU*VMIIIIUFUUUN/                 ", 5, 3, 6);
					OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", 5, 4, 6);
					OnDrawText((char*)"**", 54, 4, 12);
					OnDrawText((char*)"**", 64, 4, 12);
					OnDrawText((char*)"VV", 24, 4, 13);
					OnDrawText((char*)"VV", 36, 4, 13);
					OnDrawText((char*)"VV", 82, 4, 13);
					OnDrawText((char*)"VV", 94, 4, 13);
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 5, 6);
					OnDrawText((char*)"***", 54, 5, 12);
					OnDrawText((char*)"***", 63, 5, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 6, 6);
					OnDrawText((char*)"***", 55, 6, 12);
					OnDrawText((char*)"***", 62, 6, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 7, 6);
					OnDrawText((char*)"***", 56, 7, 12);
					OnDrawText((char*)"***", 61, 7, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 8, 6);
					OnDrawText((char*)"**::**", 57, 8, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 9, 6);
					OnDrawText((char*)"****", 58, 9, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 10, 6);
					OnDrawText((char*)"**", 59, 10, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 11, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 12, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 13, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 14, 6);
				}
				if ((StoryTime + 1500 < GetTickCount64()) && (StoryTime + 1599 > GetTickCount64()))
				{
					OnDrawText((char*)" MMMVM*::**::*****::::::*****:..::***:**IVFVVVVVI*****VV*****NBVFIII**:****::::*******:::*******:******NNVMNM ", 5, 0, 6);
					OnDrawText((char*)"      NN************:******V**:::*******IIVVVVIIIV**********VVVVVIIV********:::*VVV**************VVFFIIM      ", 5, 1, 6);
					OnDrawText((char*)"VV", 7, 1, 13);
					OnDrawText((char*)"VV", 111, 1, 13);
					OnDrawText((char*)"        NMMMFVVVV***::******************IVIVVVFVFVV********IVVVVVIIM:.*V*******V*********VVVFIIIMMMNNN        ", 5, 2, 6);
					OnDrawText((char*)"              NNNM*VVVVVVV*NNNVVFVVFFF**BNFFVVFFFVVV******IFVVIVFIII**VV*NFVVFF*VVVVFVVVVV:MNNNN              ", 5, 3, 6);
					OnDrawText((char*)"VV", 15, 3, 13);
					OnDrawText((char*)"VV", 103, 3, 13);
					OnDrawText((char*)"                LNNFNNMFIIIIUUBUUFUUVVVUUUVFVVVVFFVVV****VIFFVVVFIMIUUUVUVUUUUU*VMIIIIUFUUUN/                 ", 5, 4, 6);
					OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", 5, 5, 6);
					OnDrawText((char*)"**", 54, 5, 12);
					OnDrawText((char*)"**", 64, 5, 12);
					OnDrawText((char*)"VV", 24, 5, 13);
					OnDrawText((char*)"VV", 36, 5, 13);
					OnDrawText((char*)"VV", 82, 5, 13);
					OnDrawText((char*)"VV", 94, 5, 13);
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 6, 6);
					OnDrawText((char*)"***", 54, 6, 12);
					OnDrawText((char*)"***", 63, 6, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 7, 6);
					OnDrawText((char*)"***", 55, 7, 12);
					OnDrawText((char*)"***", 62, 7, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 8, 6);
					OnDrawText((char*)"***", 56, 8, 12);
					OnDrawText((char*)"***", 61, 8, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 9, 6);
					OnDrawText((char*)"**::**", 57, 9, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 10, 6);
					OnDrawText((char*)"****", 58, 10, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 11, 6);
					OnDrawText((char*)"**", 59, 11, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 12, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 13, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 14, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 15, 6);
				}
				if ((StoryTime + 1600 < GetTickCount64()) && (StoryTime + 1699 > GetTickCount64()))
				{
					OnDrawText((char*)"MMM::*********::::::.:::***:::..:**:::*:IVVVVFFV*****VVVV*****VVFIII:..::**::::******:::::::**:***********VMMM", 5, 0, 6);
					OnDrawText((char*)" MMMVM*::**::*****::::::*****:..::***:**IVFVVVVVI*****VV*****NBVFIII**:****::::*******:::*******:******NNVMNM ", 5, 1, 6);
					OnDrawText((char*)"      NN************:******V**:::*******IIVVVVIIIV**********VVVVVIIV********:::*VVV**************VVFFIIM      ", 5, 2, 6);
					OnDrawText((char*)"VV", 7, 2, 13);
					OnDrawText((char*)"VV", 111, 2, 13);
					OnDrawText((char*)"        NMMMFVVVV***::******************IVIVVVFVFVV********IVVVVVIIM:.*V*******V*********VVVFIIIMMMNNN        ", 5, 3, 6);
					OnDrawText((char*)"              NNNM*VVVVVVV*NNNVVFVVFFF**BNFFVVFFFVVV******IFVVIVFIII**VV*NFVVFF*VVVVFVVVVV:MNNNN              ", 5, 4, 6);
					OnDrawText((char*)"VV", 15, 4, 13);
					OnDrawText((char*)"VV", 103, 4, 13);
					OnDrawText((char*)"                LNNFNNMFIIIIUUBUUFUUVVVUUUVFVVVVFFVVV****VIFFVVVFIMIUUUVUVUUUUU*VMIIIIUFUUUN/                 ", 5, 5, 6);
					OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", 5, 6, 6);
					OnDrawText((char*)"**", 54, 6, 12);
					OnDrawText((char*)"**", 64, 6, 12);
					OnDrawText((char*)"VV", 24, 6, 13);
					OnDrawText((char*)"VV", 36, 6, 13);
					OnDrawText((char*)"VV", 82, 6, 13);
					OnDrawText((char*)"VV", 94, 6, 13);
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 7, 6);
					OnDrawText((char*)"***", 54, 7, 12);
					OnDrawText((char*)"***", 63, 7, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 8, 6);
					OnDrawText((char*)"***", 55, 8, 12);
					OnDrawText((char*)"***", 62, 8, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 9, 6);
					OnDrawText((char*)"***", 56, 9, 12);
					OnDrawText((char*)"***", 61, 9, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 10, 6);
					OnDrawText((char*)"**::**", 57, 10, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 11, 6);
					OnDrawText((char*)"****", 58, 11, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 12, 6);
					OnDrawText((char*)"**", 59, 12, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 13, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 14, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 15, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 16, 6);
				}
				if ((StoryTime + 1700 < GetTickCount64()) && (StoryTime + 1799 > GetTickCount64()))
				{
					OnDrawText((char*)"MMM::.:.::.:::::.:::..:****:::..:****:::I**VNBF*****VVUUVV*****VFFF*::::*::*:::::*****:::**::*********:****MMM", 5, 0, 6);
					OnDrawText((char*)"MMM::*********::::::.:::***:::..:**:::*:IVVVVFFV*****VVVV*****VVFIII:..::**::::******:::::::**:***********VMMM", 5, 1, 6);
					OnDrawText((char*)" MMMVM*::**::*****::::::*****:..::***:**IVFVVVVVI*****VV*****NBVFIII**:****::::*******:::*******:******NNVMNM ", 5, 2, 6);
					OnDrawText((char*)"      NN************:******V**:::*******IIVVVVIIIV**********VVVVVIIV********:::*VVV**************VVFFIIM      ", 5, 3, 6);
					OnDrawText((char*)"VV", 7, 3, 13);
					OnDrawText((char*)"VV", 111, 3, 13);
					OnDrawText((char*)"        NMMMFVVVV***::******************IVIVVVFVFVV********IVVVVVIIM:.*V*******V*********VVVFIIIMMMNNN        ", 5, 4, 6);
					OnDrawText((char*)"              NNNM*VVVVVVV*NNNVVFVVFFF**BNFFVVFFFVVV******IFVVIVFIII**VV*NFVVFF*VVVVFVVVVV:MNNNN              ", 5, 5, 6);
					OnDrawText((char*)"VV", 15, 5, 13);
					OnDrawText((char*)"VV", 103, 5, 13);
					OnDrawText((char*)"                LNNFNNMFIIIIUUBUUFUUVVVUUUVFVVVVFFVVV****VIFFVVVFIMIUUUVUVUUUUU*VMIIIIUFUUUN/                 ", 5, 6, 6);
					OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", 5, 7, 6);
					OnDrawText((char*)"**", 54, 7, 12);
					OnDrawText((char*)"**", 64, 7, 12);
					OnDrawText((char*)"VV", 24, 7, 13);
					OnDrawText((char*)"VV", 36, 7, 13);
					OnDrawText((char*)"VV", 82, 7, 13);
					OnDrawText((char*)"VV", 94, 7, 13);
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 8, 6);
					OnDrawText((char*)"***", 54, 8, 12);
					OnDrawText((char*)"***", 63, 8, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 9, 6);
					OnDrawText((char*)"***", 55, 9, 12);
					OnDrawText((char*)"***", 62, 9, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 10, 6);
					OnDrawText((char*)"***", 56, 10, 12);
					OnDrawText((char*)"***", 61, 10, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 11, 6);
					OnDrawText((char*)"**::**", 57, 11, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 12, 6);
					OnDrawText((char*)"****", 58, 12, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 13, 6);
					OnDrawText((char*)"**", 59, 13, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 14, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 15, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 16, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 17, 6);
				}
				if ((StoryTime + 1800 < GetTickCount64()) && (StoryTime + 1899 > GetTickCount64()))
				{
					OnDrawText((char*)"MMMMFVVVVFVVIMMMMMMMMMMNMNNMNNMMMMMNNNNNUUUUU******VVVUUVVV*****VUVFIMMMMMIFIMMMIFFFIIIIVVVVFVVVNNMMMNNMMVMNNM", 5, 0, 6);
					OnDrawText((char*)"MMM::.:.::.:::::.:::..:****:::..:****:::I**VNBF*****VVUUVV*****VFFF*::::*::*:::::*****:::**::*********:****MMM", 5, 1, 6);
					OnDrawText((char*)"MMM::*********::::::.:::***:::..:**:::*:IVVVVFFV*****VVVV*****VVFIII:..::**::::******:::::::**:***********VMMM", 5, 2, 6);
					OnDrawText((char*)" MMMVM*::**::*****::::::*****:..::***:**IVFVVVVVI*****VV*****NBVFIII**:****::::*******:::*******:******NNVMNM ", 5, 3, 6);
					OnDrawText((char*)"      NN************:******V**:::*******IIVVVVIIIV**********VVVVVIIV********:::*VVV**************VVFFIIM      ", 5, 4, 6);
					OnDrawText((char*)"VV", 7, 4, 13);
					OnDrawText((char*)"VV", 111, 4, 13);
					OnDrawText((char*)"        NMMMFVVVV***::******************IVIVVVFVFVV********IVVVVVIIM:.*V*******V*********VVVFIIIMMMNNN        ", 5, 5, 6);
					OnDrawText((char*)"              NNNM*VVVVVVV*NNNVVFVVFFF**BNFFVVFFFVVV******IFVVIVFIII**VV*NFVVFF*VVVVFVVVVV:MNNNN              ", 5, 6, 6);
					OnDrawText((char*)"VV", 15, 6, 13);
					OnDrawText((char*)"VV", 103, 6, 13);
					OnDrawText((char*)"                LNNFNNMFIIIIUUBUUFUUVVVUUUVFVVVVFFVVV****VIFFVVVFIMIUUUVUVUUUUU*VMIIIIUFUUUN/                 ", 5, 7, 6);
					OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", 5, 8, 6);
					OnDrawText((char*)"**", 54, 8, 12);
					OnDrawText((char*)"**", 64, 8, 12);
					OnDrawText((char*)"VV", 24, 8, 13);
					OnDrawText((char*)"VV", 36, 8, 13);
					OnDrawText((char*)"VV", 82, 8, 13);
					OnDrawText((char*)"VV", 94, 8, 13);
					OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", 5, 9, 6);
					OnDrawText((char*)"***", 54, 9, 12);
					OnDrawText((char*)"***", 63, 9, 12);
					OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", 5, 10, 6);
					OnDrawText((char*)"***", 55, 10, 12);
					OnDrawText((char*)"***", 62, 10, 12);
					OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", 5, 11, 6);
					OnDrawText((char*)"***", 56, 11, 12);
					OnDrawText((char*)"***", 61, 11, 12);
					OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", 5, 12, 6);
					OnDrawText((char*)"**::**", 57, 12, 12);
					OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", 5, 13, 6);
					OnDrawText((char*)"****", 58, 13, 12);
					OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", 5, 14, 6);
					OnDrawText((char*)"**", 59, 14, 12);
					OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", 5, 15, 6);
					OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", 5, 16, 6);
					OnDrawText((char*)"                                                   VUUUUUUV                                                   ", 5, 17, 6);
					OnDrawText((char*)"                                                     VUUV                                                     ", 5, 18, 6);
				}
				if ((StoryTime + 1900 < GetTickCount64()) && (StoryTime + 1999 > GetTickCount64()))
					BossScene(1);				
				if(StoryTime + 2000 < GetTickCount64())
					BossScene(2);
				OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
				if(StoryTime + 2100 < GetTickCount64())
					BossTuto();
				if (StoryTime + 2100 < GetTickCount64())
					Story4 = false;			
			}		
		}
		while ((StoryTime + 2100 < GetTickCount64()))
		{
			if (GetAsyncKeyState(VK_ESCAPE))
				break;
		}
		Heat = 0.0f;
		EnemyTime = GetTickCount64();
		Cooling = GetTickCount64();
		ERR = GetTickCount64();
		Loaded = GetTickCount64();
		DropItem = GetTickCount64();
		BuffTime = GetTickCount64();
		Time = GetTickCount64();
		ClearTime = GetTickCount64();
		Load = false;
		OHeat = false;
		Boss->BTime = GetTickCount64();
		Boss->MTime = GetTickCount64();

		while (Boss->HP > 0)
		{
			if (Time + 20 < GetTickCount64())
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

				if (Boss->BTime + 2500 < GetTickCount64() && Boss->BTime + 2550 > GetTickCount64())
				{					
					for (int i = 0; i < 120; ++i)
					{
						if (bBullet[i] == nullptr && bBullet[i + 1] == nullptr && bBullet[i + 2] == nullptr &&
							bBullet[i + 3] == nullptr && bBullet[i + 4] == nullptr && bBullet[i + 5] == nullptr &&
							bBullet[i + 6] == nullptr && bBullet[i + 7] == nullptr)
						{
							bBullet[i] = BossBullet(29, 15);
							Dir[i] = GetDirection(Player, bBullet[i]);
							bBullet[i + 1] = BossBullet(31, 15);
							Dir[i + 1] = GetDirection(Player, bBullet[i + 1]);
							bBullet[i + 2] = BossBullet(41, 16);
							Dir[i + 2] = GetDirection(Player, bBullet[i + 2]);
							bBullet[i + 3] = BossBullet(43, 16);	    
							Dir[i + 3] = GetDirection(Player, bBullet[i + 3]);
							bBullet[i + 4] = BossBullet(75, 16);	       
							Dir[i + 4] = GetDirection(Player, bBullet[i + 4]);
							bBullet[i + 5] = BossBullet(77, 16);	       
							Dir[i + 5] = GetDirection(Player, bBullet[i + 5]);
							bBullet[i + 6] = BossBullet(87, 15);	       
							Dir[i + 6] = GetDirection(Player, bBullet[i + 6]);
							bBullet[i + 7] = BossBullet(89, 15);	       
							Dir[i + 7] = GetDirection(Player, bBullet[i + 7]);
							
							break;
						}					
					}
				}
				if (Boss->BTime + 2800 < GetTickCount64() && Boss->BTime + 2850 > GetTickCount64())
				{
					for (int i = 0; i < 120; ++i)
					{
						if (bBullet[i] == nullptr && bBullet[i + 1] == nullptr && bBullet[i + 2] == nullptr &&
							bBullet[i + 3] == nullptr && bBullet[i + 4] == nullptr && bBullet[i + 5] == nullptr &&
							bBullet[i + 6] == nullptr && bBullet[i + 7] == nullptr)
						{
							bBullet[i] = BossBullet(29, 15);
							Dir[i] = GetDirection(Player, bBullet[i]);
							bBullet[i + 1] = BossBullet(31, 15);
							Dir[i + 1] = GetDirection(Player, bBullet[i + 1]);
							bBullet[i + 2] = BossBullet(41, 16);
							Dir[i + 2] = GetDirection(Player, bBullet[i + 2]);
							bBullet[i + 3] = BossBullet(43, 16);
							Dir[i + 3] = GetDirection(Player, bBullet[i + 3]);
							bBullet[i + 4] = BossBullet(77, 16);
							Dir[i + 4] = GetDirection(Player, bBullet[i + 4]);
							bBullet[i + 5] = BossBullet(79, 16);
							Dir[i + 5] = GetDirection(Player, bBullet[i + 5]);
							bBullet[i + 6] = BossBullet(89, 15);
							Dir[i + 6] = GetDirection(Player, bBullet[i + 6]);
							bBullet[i + 7] = BossBullet(91, 15);
							Dir[i + 7] = GetDirection(Player, bBullet[i + 7]);

							break;
						}
					}
				}
				if (Boss->BTime + 3100 < GetTickCount64())
				{
					Boss->BTime = GetTickCount64();
					for (int i = 0; i < 120; ++i)
					{
						if (bBullet[i] == nullptr && bBullet[i + 1] == nullptr && bBullet[i + 2] == nullptr &&
							bBullet[i + 3] == nullptr && bBullet[i + 4] == nullptr && bBullet[i + 5] == nullptr &&
							bBullet[i + 6] == nullptr && bBullet[i + 7] == nullptr)
						{
							bBullet[i] = BossBullet(29, 15);
							Dir[i] = GetDirection(Player, bBullet[i]);
							bBullet[i + 1] = BossBullet(31, 15);
							Dir[i + 1] = GetDirection(Player, bBullet[i + 1]);
							bBullet[i + 2] = BossBullet(41, 16);
							Dir[i + 2] = GetDirection(Player, bBullet[i + 2]);
							bBullet[i + 3] = BossBullet(43, 16);
							Dir[i + 3] = GetDirection(Player, bBullet[i + 3]);
							bBullet[i + 4] = BossBullet(77, 16);
							Dir[i + 4] = GetDirection(Player, bBullet[i + 4]);
							bBullet[i + 5] = BossBullet(79, 16);
							Dir[i + 5] = GetDirection(Player, bBullet[i + 5]);
							bBullet[i + 6] = BossBullet(89, 15);
							Dir[i + 6] = GetDirection(Player, bBullet[i + 6]);
							bBullet[i + 7] = BossBullet(91, 15);
							Dir[i + 7] = GetDirection(Player, bBullet[i + 7]);

							break;
						}
					}
				}

				for (int i = 0; i < 128; ++i)
				{
					if (bBullet[i] != nullptr)
					{
						for (int j = 0; j < 8; ++j)
						{
							if (Missile[j] != nullptr)
							{
								if (ECollision(Missile[j], bBullet[i]))
								{
									delete bBullet[i];
									bBullet[i] = nullptr;

									break;
								}
							}
						}
					}
					if (bBullet[i] != nullptr)
					{
						if (!PSA)
						{
							if (PCollision(bBullet[i], Player))
							{
								Player->HP--;
								HCount++;
								SpArmorP = GetTickCount64();
								PSA = true;
								delete bBullet[i];
								bBullet[i] = nullptr;
							}
						}						
					}
					if (bBullet[i] != nullptr)
					{
						if (bBullet[i]->TransInfo.Position.y >= 59)
						{
							delete bBullet[i];
							bBullet[i] = nullptr;
						}						
					}
					if (bBullet[i] != nullptr)
					{
						if (bBullet[i]->TransInfo.Position.x <= 0 || bBullet[i]->TransInfo.Position.x >= 120)
						{
							delete bBullet[i];
							bBullet[i] = nullptr;
						}
					}
				}
				
				if (Boss->MTime + 10000 < GetTickCount64())
				{
					Boss->MTime = GetTickCount64();
					for (int i = 0; i < 24; ++i)
					{
						if (bMissile[i] == nullptr && bMissile[i + 1] == nullptr && bMissile[i + 2] == nullptr &&
							bMissile[i + 3] == nullptr && bMissile[i + 4] == nullptr && bMissile[i + 5] == nullptr &&
							bMissile[i + 6] == nullptr && bMissile[i + 7] == nullptr && bMissile[i + 8] == nullptr &&
							bMissile[i + 9] == nullptr && bMissile[i + 10] == nullptr && bMissile[i + 11] == nullptr &&
							bMissile[i + 12] == nullptr && bMissile[i + 13] == nullptr && bMissile[i + 14] == nullptr && bMissile[i + 15] == nullptr
							)
						{
							bMissile[i] = CreateBullet(7, 6);
							bMissile[i + 1] = CreateBullet(8, 6);
							bMissile[i + 2] = CreateBullet(111, 6);
							bMissile[i + 3] = CreateBullet(112, 6);
							bMissile[i + 4] = CreateBullet(15, 8);
							bMissile[i + 5] = CreateBullet(16, 8);
							bMissile[i + 6] = CreateBullet(103, 8);
							bMissile[i + 7] = CreateBullet(104, 8);
							bMissile[i + 8] = CreateBullet(24, 10);
							bMissile[i + 9] = CreateBullet(25, 10);
							bMissile[i + 10] = CreateBullet(36, 10);
							bMissile[i + 11] = CreateBullet(37, 10);
							bMissile[i + 12] = CreateBullet(82, 10);
							bMissile[i + 13] = CreateBullet(83, 10);
							bMissile[i + 14] = CreateBullet(94, 10);
							bMissile[i + 15] = CreateBullet(95, 10);
						}
					}
				}

				for (int i = 0; i < 32; ++i)
				{
					if (bMissile[i] != nullptr)
					{
						for (int j = 0; j < 8; ++j)
						{
							if (Missile[j] != nullptr)
							{
								if (ECollision(Missile[j], bMissile[i]))
								{
									delete Missile[j];
									Missile[j] = nullptr;
									
									delete bMissile[i];
									bMissile[i] = nullptr;
								}
							}								
						}
					}
					if (bMissile[i] != nullptr)
					{
						if (!PSA)
						{
							if (PCollision(bMissile[i], Player))
							{
								Player->HP--;
								HCount++;
								SpArmorP = GetTickCount64();
								PSA = true;
								delete bMissile[i];
								bMissile[i] = nullptr;
							}
						}
					}
					if (bMissile[i] != nullptr)
					{
						if (bMissile[i]->TransInfo.Position.y >= 59)
						{
							delete bMissile[i];
							bMissile[i] = nullptr;
						}
					}
				}

				// E
				if (EnemyTime + 750 < GetTickCount64())
				{
					EnemyTime = GetTickCount64();
					for (int i = 0; i < 64; ++i)
					{
						if (Enemy[i] == nullptr)
						{
							srand((GetTickCount() + i * i) * GetTickCount());
							Enemy[i] = CreateEnemy((rand() % 114 + 2), 26.0f, EnemyTime);
							Enemy[i]->Enemy.ETime = GetTickCount64();

							break;
						}
					}
				}
				// EBullet
				for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i] != nullptr)
					{
						srand((GetTickCount() + i * i) * GetTickCount());
						if (Enemy[i]->Enemy.ETime + (rand() % 500 + 500) < GetTickCount64())
						{
							Enemy[i]->Enemy.ETime = GetTickCount64();
							for (int j = 0; j < 256; ++j)
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
				UpdateInput(Player);
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
						if (Cooling + 500 < GetTickCount64())
						{
							Cooling = GetTickCount64();
							if (Heat > 0)
								Heat -= 1.0f;
							if (Heat < 0)
								Heat = 0;
						}
					}
				}
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

								Loaded = GetTickCount64();
								break;
							}
						}
					}
				}

				if (DropItem + 11000 < GetTickCount64())
				{
					DropItem = GetTickCount64();
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

				if (BBuff || MBuff)
				{
					if (BuffTime + 10000 < GetTickCount64())
					{
						BBuff = false;
						MBuff = false;
					}
				}

				if (PSA)
				{
					if (SpArmorP + 1500 < GetTickCount64())
						PSA = false;
				}

				if (BSA)
				{
					if (SpArmorB + 3000 < GetTickCount64())
						BSA = false;
				}

				for (int i = 0; i < 256; ++i)
				{
					if (Bullet[i] != nullptr)
					{
						for (int j = 0; j < 8; ++j)
						{
							if (HB[j]->Option == 1)
							{
								if (Hit(HB[j], Bullet[i]))
								{
									HB[j]->Option = 2;
									HB[j]->HTime = GetTickCount64();
									Boss->HP--;
									ScoreP(2000);
									Score += 2000;
								}
							}							
						}
						if (!BSA)
						{
							if (BridgeHit(Bullet[i], 2))
							{
								BSA = true;
								SpArmorB = GetTickCount64();
								Boss->HP--;
								ScoreP(2000);
								Score += 2000;
							}
						}
					}
				}

				for (int i = 0; i < 32; ++i)
				{
					if (Missile[i] != nullptr)
					{
						for (int j = 0; j < 8; ++j)
						{
							if (HB[j]->Option == 1)
							{
								if (Hit(HB[j], Missile[i]))
								{
									HB[j]->Option = 2;
									HB[j]->HTime = GetTickCount64();
									Boss->HP -= 2;
									ScoreP(4000);
									Score += 4000;
								}
							}							
						}
						if (!BSA)
						{
							if (BridgeHit(Missile[i], 2))
							{
								BSA = true;
								SpArmorB = GetTickCount64();
								Boss->HP -= 5;
								ScoreP(10000);
								Score += 10000;
							}
						}
					}
				}
				for (int i = 0; i < 8; ++i)
				{
					if (HB[i] != nullptr)
					{
						if (HB[i]->Option == 2)
						{
							if (HB[i]->HTime + 3000 < GetTickCount64())
								HB[i]->Option = 1;
						}
					}
				}
				// 플레이어 뷸렛 / 에너미 충돌
				for (int i = 0; i < 256; ++i)
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
							if (Bullet[i]->TransInfo.Position.y <= 3)
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
							if (Missile[i]->TransInfo.Position.y <= 3)
							{
								delete Missile[i];
								Missile[i] = nullptr;
							}
						}

					}
				}

				// 에너미 뷸렛 / 미사일 충돌
				for (int i = 0; i < 256; ++i)
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
						if (!PSA)
						{
							if (PCollision(EBullet[i], Player))
							{
								Player->HP--;
								HCount++;
								PSA = true;
								SpArmorP = GetTickCount64();
								delete EBullet[i];
								EBullet[i] = nullptr;

								break;
							}
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
								BuffTime = GetTickCount64();
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
								BuffTime = GetTickCount64();
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

				BossScene(2);
				for (int i = 0; i < 8; ++i)
				{
					if (HB[i])
						OnDrawHB(HB[i]);
				}
				OnDrawBridge(2);

				for (int i = 0; i < 128; ++i)
				{
					if (bBullet[i])
					{
						OnDrawText(bBullet[i]->bBullet.Texture,
							bBullet[i]->TransInfo.Position.x,
							bBullet[i]->TransInfo.Position.y, 12);

						bBullet[i]->TransInfo.Position.x += Dir[i].x;
						bBullet[i]->TransInfo.Position.y += 1.5f;
					}
				}

				if (Boss->MTime + 8000 < GetTickCount64() && Boss->MTime + 8999)
				{
					OnDrawText((char*)"!!", 7, 7, 14);
					OnDrawText((char*)"!!", 111, 7, 14);
					OnDrawText((char*)"!!", 15, 9, 14);
					OnDrawText((char*)"!!", 103, 9, 14);
					OnDrawText((char*)"!!", 24, 11, 14);
					OnDrawText((char*)"!!", 36, 11, 14);
					OnDrawText((char*)"!!", 82, 11, 14);
					OnDrawText((char*)"!!", 94, 11, 14);
				}
				if (Boss->MTime + 9000 < GetTickCount64() && Boss->MTime + 9999)
				{
					OnDrawText((char*)"!!", 7, 7, 12);
					OnDrawText((char*)"!!", 111, 7, 12);
					OnDrawText((char*)"!!", 15, 9, 12);
					OnDrawText((char*)"!!", 103, 9, 12);
					OnDrawText((char*)"!!", 24, 11, 12);
					OnDrawText((char*)"!!", 36, 11, 12);
					OnDrawText((char*)"!!", 82, 11, 12);
					OnDrawText((char*)"!!", 94, 11, 12);
				}

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

				for (int i = 0; i < 32; ++i)
				{
					if (bMissile[i])
					{
						OnDrawText(bMissile[i]->bMissile.Texture, bMissile[i]->TransInfo.Position.x, bMissile[i]->TransInfo.Position.y, 13);
						bMissile[i]->TransInfo.Position.y += 2.5;
					}
				}
				// EB
				for (int i = 0; i < 256; ++i)
				{
					if (EBullet[i])
					{
						OnDrawText(EBullet[i]->Bullet.Texture,
							EBullet[i]->TransInfo.Position.x,
							EBullet[i]->TransInfo.Position.y, 12);

						EBullet[i]->TransInfo.Position.y += 1.0f;
					}
				}

				// 미사일 
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

				for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i])
					{
						OnDrawObj(Enemy[i], Enemy[i]->TransInfo.Position.x, Enemy[i]->TransInfo.Position.y);
						Direction = GetDirection(Player, Enemy[i]);
						if (Enemy[i]->Enemy.ETime + (rand() % 500 + 500) < GetTickCount64())
						{
							Enemy[i]->Enemy.ETime = GetTickCount64();
							EnemyMove(Enemy[i], Direction, rand() % 5, 1);
						}
					}
				}
				if(!PSA)
					OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
				else if (PSA)
				{
					if(SpArmorP + 250 < GetTickCount64() && SpArmorP + 499 > GetTickCount64())
						OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
					if(SpArmorP + 750 < GetTickCount64() && SpArmorP + 999 > GetTickCount64())
						OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
					if(SpArmorP + 1250 < GetTickCount64() && SpArmorP + 1499 > GetTickCount64())
						OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);
				}
				if (!Load)
				{
					if (Loaded - GetTickCount64() >= -999)
						OnDrawText(5, 78.0f, 0, 14);
					else if (Loaded - GetTickCount64() >= -1999)
						OnDrawText(4, 78.0f, 0, 14);
					else if (Loaded - GetTickCount64() >= -2999)
						OnDrawText(3, 78.0f, 0, 14);
					else if (Loaded - GetTickCount64() >= -3999)
						OnDrawText(2, 78.0f, 0, 14);
					else if (Loaded - GetTickCount64() >= -4999)
						OnDrawText(1, 78.0f, 0, 14);
					else if (Loaded - GetTickCount64() <= -5000 &&
						Loaded - GetTickCount64() >= -5049)
						Load = true;
				}
				if (Loaded - GetTickCount64() <= -5000)
					OnDrawText((char*)"Loaded", 76.0f, 0.0f, 10);

				OnDrawText((char*)"SCORE : ", 1.0f, 0.0f);
				OnDrawText(Score, 9.0f, 0.0f, 14);

				OnDrawText((char*)"Missile : ", 66.0f, 0.0f);

				OnDrawText((char*)"Heat Gauge : [                    ]", 84.0f, 0.0f);

				// 오버히트
				for (int i = 0; i < Heat; ++i)
				{
					OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 10);
					if (7.9f >= Heat && Heat >= 5.0f)
					{
						ERR = GetTickCount64();
						OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 14);
					}

					if (9.9f >= Heat && Heat >= 8.0f)
					{
						ERR = GetTickCount64();
						OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 12);
					}
					if (Heat >= 10.0f)
					{
						OHeat = true;
						OnDrawText((char*)"[ O V E R H E A T ! !]", 97.0f, 0.0f, 12);

						if (ERR + 3000 < GetTickCount64())
						{
							ERR = GetTickCount64();
							OHeat = false;
							Heat = 0.0f;
						}

					}
				}
				
				OnDrawText((char*)"HP : ", 40.0f, 0.0f, 10);
				for (int i = 1; i <= Player->HP; ++i)
				{
					OnDrawText((char*)"♥", 44.0f + i * 2, 0.0f, 10);
					if (Player->HP <= 3)
						OnDrawText((char*)"♥", 44.0f + i * 2, 0.0f, 14);
					if (Player->HP == 1)
						OnDrawText((char*)"♥", 44.0f + i * 2, 0.0f, 12);
					//if (i <= 0)
					// 게임 엔드
				}

				for (int i = 0; i < Boss->HP; ++i)
				{
					OnDrawText((char*)"■", 0 + i * 2, 1, 12);
				}
			}
		}
		for (int i = 0; i < 64; ++i)
		{
			if (Enemy[i] != nullptr)
			{
				delete Enemy[i];
				Enemy[i] = nullptr;
			}
		}
		for (int i = 0; i < 256; ++i)
		{
			if (Bullet[i] != nullptr)
			{
				delete Bullet[i];
				Bullet[i] = nullptr;
			}
		}
		for (int i = 0; i < 128; ++i)
		{
			if (bBullet[i] != nullptr)
			{
				delete bBullet[i];
				bBullet[i] = nullptr;
			}
		}
		for (int i = 0; i < 256; ++i)
		{
			if (EBullet[i] != nullptr)
			{
				delete EBullet[i];
				EBullet[i] = nullptr;
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
		for (int i = 0; i < 32; ++i)
		{
			if (bMissile[i] != nullptr)
			{
				delete bMissile[i];
				bMissile[i] = nullptr;
			}
		}
		for (int i = 0; i < 2; ++i)
		{
			if (Item[i] != nullptr)
			{
				delete Item[i];
				Item[i] = nullptr;
			}
		}

		
	}
	return 0;
}