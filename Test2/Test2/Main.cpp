#include "Headers.h"
// v 0.1 �÷��̾�, ���ʹ�
// v 0.2 �淿 ����, ���� ��Ʈ
// v 0.3 �̻���, �浹
// v 0.4 HP, ���ھ�, ���
// v 0.5 ������ ���
// v 0.6 �ΰ�, ����, ������
// ������ �Ұ� : �ʹ� ���丮, Ʃ�丮��
/*
1. �Ķ�
2. ��Ʈ����
3. �������� �ϴ�
4. ����
5. ����Ÿ
6. ¤
7. ���
8. ȸ��
9. �Ķ�
10. ���λ�
11. �ϴû�
12. ����
13. ��ȫ
14. ���
15. ���� ���
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
		// �ΰ�
		if (first)
		{
			LogoScene(logo, Logo, Loading);
			first = false;
		}
		// ����
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

		// ���丮1(Ʃ�丮��)
		while (Story1)
		{
			Tutorial(Player, Time, Enemy1, Enemy2, Enemy3);
		}
		delete Enemy1;
		delete Enemy2;
		delete Enemy3;
		EnemyTime1 = GetTickCount64();
		Cooling1 = GetTickCount64();
		ERR1 = GetTickCount64();
		Loaded1 = GetTickCount64();
		DropItem1 = GetTickCount64();
		BuffTime1 = GetTickCount64();
		ULONGLONG R1Time = GetTickCount64();
		while (R1Time + 60000 > GetTickCount64())
		{
			if (Time + 15 < GetTickCount64())
			{
				Time = GetTickCount64();
				system("cls");

				// ���
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

				// ���ʹ� ����
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

				// ���ʹ� �淿 ����
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

				// �̵�
				if (!Story)
					UpdateInput(Player);

				// �����̽��� �淿
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
								if (!Buff)
								{
									Bullet[i] = CreateBullet(
										Player->TransInfo.Position.x - 2,
										Player->TransInfo.Position.y + 1);
									Bullet[i + 1] = CreateBullet(
										Player->TransInfo.Position.x + 2,
										Player->TransInfo.Position.y + 1);
								}
								else if (Buff)
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

				// �̻���			
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
								Missile[i]->HP = 2;
								Loaded1 = GetTickCount64();
								break;
							}
						}
					}
				}

				// ������ ����
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

				// �÷��̾� �淿 / ���ʹ� �浹
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
									Kill++;
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

				// ���ʹ� / �̻��� �浹
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
									Kill++;

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

				// ���ʹ� �淿 / �̻��� �浹
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

				// ������
				for (int i = 0; i < 2; ++i)
				{
					if (Item[i] != nullptr)
					{
						if (PCollision(Item[i], Player))
						{
							if (Item[i]->Item.Option == 1)
							{
								BuffTime1 = GetTickCount64();
								Buff = true;
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

				// Enemy 20 �̻��� �� fail
				/*for (int i = 0; i < 64; ++i)
				{
					if (Enemy[i] != nullptr)
					{
						ECount++;
						if (ECount >= 20)
						{
							ECount = 0;
							// ���� ����
						}
					}
				}*/

				// ��� ���
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
				// �÷��̾� �淿 ���
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

				// ���ʹ� �淿
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

				// �̻��� ���
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

				if (Buff)
				{
					if (BuffTime1 + 10000 < GetTickCount64())
					{
						Buff = false;
					}
				}
				// �̻��� ��
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

				// ���ʹ� ����
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

				// ������Ʈ
				for (int i = 0; i < Heat; ++i)
				{
					OnDrawText((char*)"��", 98.0f + i * 2, 0.0f, 10);
					if (7.9f >= Heat && Heat >= 5.0f)
					{
						ERR1 = GetTickCount64();
						OnDrawText((char*)"��", 98.0f + i * 2, 0.0f, 14);
					}

					if (9.9f >= Heat && Heat >= 8.0f)
					{
						ERR1 = GetTickCount64();
						OnDrawText((char*)"��", 98.0f + i * 2, 0.0f, 12);
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

				// HP ��
				OnDrawText((char*)"HP : ", 50.0f, 0.0f, 10);
				for (int i = 1; i <= Player->HP; ++i)
				{
					OnDrawText((char*)"��", 54.0f + i * 2, 0.0f, 10);
					if (Player->HP <= 3)
						OnDrawText((char*)"��", 54.0f + i * 2, 0.0f, 14);
					if (Player->HP == 1)
						OnDrawText((char*)"��", 54.0f + i * 2, 0.0f, 12);
					//if (i <= 0)
					// ���� ����
				}

				OnDrawText((char*)"���� �ð� : ", 50.0f, 1.0f, 14);
				for (T = 0; T < (R1Time + 60000 - GetTickCount64()) / 1000; ++T)
				{
					if (T >= (R1Time + 60000 - GetTickCount64()) / 1000)
						T = 0;
				}
				OnDrawText(T, 64.0f, 1.0f, 14);

			}
		}		

		/*
			for (int i = 0; i < 6; ++i)
		{
			if (Ally[i] == nullptr)
			{
				if (i < 3)
					Ally[i] = CreateAlly(14.0f + 15 * i, 50.0f, i);
				else if (i >= 3)
					Ally[i] = CreateAlly(30 + 15 * i, 50.0f, i);
				break;
			}
		}
			for (int i = 0; i < 6; ++i)
		{
			if (Ally[i])
				OnDrawObj(Ally[i], Ally[i]->TransInfo.Position.x, Ally[i]->TransInfo.Position.y);
		}
		*/
	}
		
	return 0;
}