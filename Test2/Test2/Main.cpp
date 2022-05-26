#include "Headers.h"
// v 0.1 ÇÃ·¹ÀÌ¾î, ¿¡³Ê¹Ì ¸¸µë
// v 0.2 ºæ·¿ »ý¼º, ¿À¹ö È÷Æ®

/*
1. ÆÄ¶û
2. ¸ÅÆ®¸¯½º
3. ¿ìÁßÃæÇÑ ÇÏ´Ã
4. ¼®·ù
5. ¸¶Á¨Å¸
6. Â¤
7. Èò»ö
8. È¸»ö
9. ÆÄ¶û
10. ¿¬µÎ»ö
11. ÇÏ´Ã»ö
12. »¡°­
13. ºÐÈ«
14. ³ë¶û
15. ¹àÀº Èò»ö
*/


int main(void)
{
	HideCursor(false);

	system("mode con:cols=120 lines=60");

	Object* Player = new Object;
	PInitialize(Player, 60.0f, 40.0f);

	Object* Enemy = new Object;
	EInitialize(Enemy, 60.0f, 10.0f);

	Player->Player.Name = (char*)"°í±æµ¿";

	Object* Bullet[128] = { nullptr };


	ULONGLONG Time = GetTickCount64();
	ULONGLONG EnemyTime = GetTickCount64();
	ULONGLONG Cooling = GetTickCount64();
	ULONGLONG ERR = GetTickCount64();

	bool Check = false;
	bool OHeat = false;
	float Heat = 0.0f;

	while (true)
	{
		if (Time + 1000 < GetTickCount64())
		{
			system("cls");

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
						Heat -= 1.0f;
					}
				}
			}
			
			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i] != nullptr)
				{
					if (Bullet[i]->TransInfo.Position.y <= 1)
					{
						delete Bullet[i];
						Bullet[i] = nullptr;
					}
				}
			}

			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i])
				{
					Bullet[i]->TransInfo.Position.y -= 1.5f;

					OnDrawText(Bullet[i]->Bullet.Texture,
						Bullet[i]->TransInfo.Position.x,
						Bullet[i]->TransInfo.Position.y, 14);					
				}
			}

			OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);

			OnDrawObj(Enemy, Enemy->TransInfo.Position.x, Enemy->TransInfo.Position.y);

			OnDrawText((char*)"[                    ]", 97.0f, 56.0f);

			for (int i = 0; i < Heat; ++i)
			{
				OnDrawText((char*)"¡á", 98.0f + i * 2, 56.0f, 10);
				if (7.9f >= Heat && Heat >= 5.0f)
					OnDrawText((char*)"¡á", 98.0f + i * 2, 56.0f, 14);

				if (9.9f >= Heat && Heat >= 8.0f)
					OnDrawText((char*)"¡á", 98.0f + i * 2, 56.0f, 12);
				if (Heat >= 10.0f)
				{
					OnDrawText((char*)"[ O V E R H E A T ! !]", 97.0f, 56.0f, 12);
					OHeat = true;
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