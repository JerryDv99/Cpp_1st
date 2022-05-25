#include "Headers.h"
// v 0.1 ÇÃ·¹ÀÌ¾î, ¿¡³Ê¹Ì ¸¸µë


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

	ULONGLONG Time = GetTickCount64();
	Object* Player = new Object;
	PInitialize(Player, 60.0f, 40.0f);

	Object* Enemy = new Object;
	EInitialize(Enemy, 60.0f, 10.0f);

	Player->Player.Name = (char*)"°í±æµ¿";

	while (true)
	{
		if (Time + 80 < GetTickCount64())
		{
			system("cls");

			UpdateInput(Player);

			OnDrawObj(Player, Player->TransInfo.Position.x, Player->TransInfo.Position.y);

			OnDrawObj(Enemy, Enemy->TransInfo.Position.x, Enemy->TransInfo.Position.y);
		}
		
	}


	return 0;
}