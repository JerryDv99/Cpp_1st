// Framework v 0.3
// �÷��̾� ���� ������ ����ü �浹

// Bullet�� ���Ϳ� �浹 �� Bullet ����
#include "Headers.h"

int main(void)
{

	HideCursor(false); // Ŀ���� ����

	// ��� �ʱ�ȭ
	
	DrawTextInfo BackGround[30];


	for (int i = 0; i < 30; ++i)
	{
		// �������� �ʱ�ȭ ����, ū ���� ���� �� �ֵ��� time������ ������ ��������
		// for���� ������ ���ԵǸ� time�� ���������� ���� �� �ֱ� ������
		// �������̶�� �ϴ��� �������� ���� ���� ���� �� ����
		// i�� ���� ���ϰ� ���������ν� �ߺ����� ������ �ʵ��� ����
		srand((GetTickCount() + i * i)* GetTickCount());


		// ���� ��� ������� ������ �ʾ�����, ���� ���� �Ѿ��� �������� �÷��̾ ���� �������
		// �Ѿ˿� ����� ������ �浹������ �ǵ��� �������� ����
		BackGround[i].Info.Option = 0;

		// ��ǥ�� �������� ����
		BackGround[i].TransInfo.Position.x = rand() % 100 + 10;
		BackGround[i].TransInfo.Position.y = rand() % 26 + 1;

		BackGround[i].Info.Texture = (char*)"*";

		BackGround[i].Info.Color = rand() % 8 + 1;

	}

	// ** �÷��̾� ���� �� �����Ҵ�
	Object* Player = new Object;

	// ** �÷��̾� �ʱ�ȭ
	Initialize(Player, (char*)"=>-", 30, 10);

	Object* Enemy[32]; // = new Object;
	Enemy[0] = new Object;
	Initialize(Enemy[0], (char*)"-<=", 80, 10);
	for (int i = 1; i < 32; ++i)
		Enemy[i] = nullptr;

	// ���� �ð����� �ʱ�ȭ
	ULONGLONG Time = GetTickCount64();
	ULONGLONG EnemyTime = GetTickCount64();

	int Score = 0;

	Object* Bullet[128] = { nullptr };
	Object* EBullet[128] = { nullptr };

	Object* Temp = new Object;

	Temp->TransInfo.Position.y = 10;
	Temp->TransInfo.Position.x = 80;

	Temp->Info.Texture = (char*)"-=";

	// ���
	while (true)
	{
		// �ʱ�ȭ�� �ð����� +50��ŭ �����ϸ�
		// �����Ӱ� ������ ������ �ð� ������ 0.5�ʷ� ����
		if (Time + 80 < GetTickCount64())
		{
			// ������ ����ŭ �ٽ� �ʱ�ȭ
			Time = GetTickCount64();

			system("cls");

			// ** ��� ���
			for (int i = 0; i < 30; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);

				// ** ������� ���� �ؽ�ó�� ������ �������� ����.
				BackGround[i].Info.Color = rand() % 8 + 1;
			}
			
			// Enemy ����
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
				// ** �����Ұ�
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
							OnDrawText((char*)"����",
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
							EBullet[i] = nullptr;	// �ݺ��� �ȿ��� delete�� ����
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
							Bullet[i] = nullptr;	// �ݺ��� �ȿ��� delete�� ����
						}
					}
				}
			}
			
			//if (Collision(Player, Enemy))
				//OnDrawText((char*)"�浹 �Դϴ�.", Enemy->TransInfo.Position.x, Enemy->TransInfo.Position.y - 1, 12);
		
			UpdateInput(Player);

			// �����̽� Ű�� �Է¹���
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

			// Player ���
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


			// sqrt : ������ �Լ�
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

					// Enemy ���
					OnDrawText(Enemy[i]->Info.Texture,
						Enemy[i]->TransInfo.Position.x,
						Enemy[i]->TransInfo.Position.y,
						12);

					//  Enemy ��ũ�� �浹
					if (Enemy[i]->TransInfo.Position.x <= 0)
					{
						delete Enemy[i];
						Enemy[i] = nullptr;
					}
				}
				
			}

			

				

			// Bullet ���
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
