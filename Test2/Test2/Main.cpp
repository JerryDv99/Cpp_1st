#include "Headers.h"
// v 0.1 �÷��̾�, ���ʹ� ����


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

	ULONGLONG Time = GetTickCount64();
	Object* Player = new Object;
	PInitialize(Player, 60.0f, 40.0f);

	Object* Enemy = new Object;
	EInitialize(Enemy, 60.0f, 10.0f);

	Player->Player.Name = (char*)"��浿";

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