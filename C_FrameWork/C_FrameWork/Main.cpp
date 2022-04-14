#define _CRT_SECURE_NO_WARNINGS	// scanf ����� ����
#include <stdio.h>
#include <string>				// ���ڿ�
#include <time.h>				// ���� ����
#include <malloc.h>				// �����Ҵ�
#include <Windows.h>			// ������

const int PLAYER	= 0;		// ���� ���Ǹ� ���� ���ȭ
const int ENEMY		= 1;

const int MAX		= 2;

int iChoice = 0;	// ������� �Է��� �޾� ��Ȳ�� ���� ����

typedef struct tagInfo			// ���� ������ ������ ����ü struct tagInfo (INFO)
{
	char* Name;
	int HP;
	int MP;

	int EXP;

	float Att;
	float Def;

	int Level;

}INFO;

typedef struct tagObject		// �÷��̾� / ���͸� ������ OBJECT ����ü
{
	INFO Info;					// INFO ����ü�� ���� ������ ������ Info 


}OBJECT;


// OBJECT ����ü ������ _Obj�� ������ ObjectType �� �Ű������� �÷��̾� / ���ʹ̸� ���� InitializeObject �Լ� ����
void InitializeObject(OBJECT* _Obj, int ObjectType);

// �÷��̾� �̸��� �Է¹��� SetName() �Լ��� ����
char* SetName();


int main(void)
{
	/*OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT*));
	InitializeObject(Player, TYPE_PLAYER);

	OBJECT* Enemy = (OBJECT*)malloc(sizeof(OBJECT*));
	InitializeObject(Enemy, TYPE_ENEMY);*/

	OBJECT* Objects[MAX];	// MAX�� ��(2)��ŭ OBJECT* Ÿ���� Objects ���� ����

	// Objects[0](PLAYER = 0���� ���ȭ) = (Objects[i]�� ������ OBJECT*Ÿ������ ����ȯ)�����Ҵ��Լ�malloc(OBJECT*�� ũ�⸸ŭ �Ҵ�)
	Objects[PLAYER] = (OBJECT*)malloc(sizeof(OBJECT*));	// Object[PLAYER]�� ����ϱ� ���� �̸� ������ �Ҵ�

	// InitializeObject �Լ��� ����� (OBJECT ����ü�� ������ PLAYER�� ������ ������ OBJECT ������ Object[PLAYER](0),int 0�� �޾� case PLAYER)
	// �� ���� ���ϴ� OBJECT* Ÿ�� ���� ����
	InitializeObject(Objects[PLAYER],PLAYER); 

	Objects[ENEMY] = (OBJECT*)malloc(sizeof(OBJECT*));	// Object[1]
	InitializeObject(Objects[ENEMY], ENEMY); 
	
	int iLoopC = 1;				// ���� ���Ḧ �����ϱ� ������ �ݺ�
	while (iLoopC)
	{
		int iLoopCheck = 1;		// ���� �ݺ����� ���� ���� �ʱ�ȭ
		while (iLoopCheck)		// Ż�� ������ ����	
		{ 
			// �ܼ� â�� ��� ����
			//system("cls");

			printf_s("\n[%s]\n", Objects[PLAYER]->Info.Name);
			printf_s("HP : %d\n", Objects[PLAYER]->Info.HP);
			printf_s("MP : %d\n", Objects[PLAYER]->Info.MP);
			printf_s("���ݷ� : %.2f\n", Objects[PLAYER]->Info.Att);
			printf_s("���� : %.2f\n", Objects[PLAYER]->Info.Def);
			printf_s("EXP : %d\n", Objects[PLAYER]->Info.EXP);
			printf_s("Level : %d\n\n", Objects[PLAYER]->Info.Level);

			printf_s("\n[%s]\n", Objects[ENEMY]->Info.Name);
			printf_s("HP : %d\n", Objects[ENEMY]->Info.HP);
			printf_s("MP : %d\n", Objects[ENEMY]->Info.MP);
			printf_s("���ݷ� : %.2f\n", Objects[ENEMY]->Info.Att);
			printf_s("���� : %.2f\n", Objects[ENEMY]->Info.Def);
			printf_s("EXP : %d\n", Objects[ENEMY]->Info.EXP);
			printf_s("Level : %d\n\n", Objects[ENEMY]->Info.Level);
			Sleep(100);			// Windows.h�� ���Ե� ������ �Լ� Sleep(1000) = 1Sec 
		
		
			printf_s("���Ϳ� �������ϴ�. �����Ͻðڽ��ϱ� ?\n1. ����\n2. ����\n�Է� : ");
			scanf_s("%d", &iChoice);

			switch (iChoice)	
			{
			case 1:				// iChoice�� 1�� ���
				printf_s("�÷��̾��� ����\n");
				Sleep(500);		

				// �÷��̾��� ���ݷ��� ������ ���º��� ���� ��� �� ���̸�ŭ ���� HP ����
				if ((Objects[PLAYER]->Info.Att > Objects[ENEMY]->Info.Def))		
					Objects[ENEMY]->Info.HP -= Objects[PLAYER]->Info.Att - Objects[ENEMY]->Info.Def;
				else
					Objects[ENEMY]->Info.HP -= 1;	// ���� ��� �ּҵ����� 1��ŭ ���� HP ����
				printf_s("������ ����\n");
				Sleep(500);

				// ������ ���ݷ��� �÷��̾��� ���º��� ���� ��� �� ���̸�ŭ �÷��̾��� HP ����
				if ((Objects[ENEMY]->Info.Att > Objects[PLAYER]->Info.Def))
					Objects[PLAYER]->Info.HP -= Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def;
				else
					Objects[PLAYER]->Info.HP -= 1;
				break;

			case 2:
				srand(time(NULL));					// time.h ���� �������� �Լ� �ʱ�ȭ
				if (rand() % 3 == 0)				// ������ ���� / 3�� �������� 0�� ���, 1/3 Ȯ���� Ż�� ����
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�. ������ �����մϴ�\n");
					Sleep(500);
					iChoice = 1;					// case 1�� ���� ����
				}
				/*else if (Objects[ENEMY]->Info.Level - Objects[PLAYER]->Info.Level >= 5)
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�. ������ �����մϴ�\n");
					iChoice = 1;
				}*/
				else
				{
					printf_s("����ġ�°Ϳ� [����] �߽��ϴ�.\n");
					iLoopCheck = 0;					// ���� ������ ���� ���� Ż��
					break;
				}
			
				Sleep(1000);
				break;

			}

			if (iLoopCheck == 0)	// ������ �����ϸ� ���� ����
				iLoopCheck = 0;
			else if (Objects[ENEMY]->Info.HP > 0 && Objects[PLAYER]->Info.HP > 0)
				iLoopCheck = 1;		// ������ �����ϰų� ������ HP�� 0�� �ɶ����� ����
			else
				iLoopCheck = 0;		// ������ �����ϰų� ������ �����ϰ� ������ HP�� 0���� ���ų� ������ Ż��

		}




		if (Objects[ENEMY]->Info.HP <= 0)		// ������ HP�� 0�� ���ų� ����, �� óġ
		{
			printf_s("���͸� óġ�߽��ϴ� !\n");
			printf_s("����ġ %d ���\n", Objects[ENEMY]->Info.EXP);
			Objects[PLAYER]->Info.EXP += Objects[ENEMY]->Info.EXP;		// �÷��̾� ����ġ�� ������ ����ġ �ջ�
			if (Objects[PLAYER]->Info.EXP >= 100)						// ����ġ�� 100 �̻��� ��� ���� ��
			{
				printf_s("�÷��̾� ������ ! ���� ���� : %d Lv\n", Objects[PLAYER]->Info.Level);
				Objects[PLAYER]->Info.EXP = 0;							// ����ġ �ʱ�ȭ
				Objects[PLAYER]->Info.Level += 1;						// �÷��̾� ������ ���� ����
				Objects[PLAYER]->Info.Att += 3;
				Objects[PLAYER]->Info.Att += 1;
			}

		}
		else if (Objects[PLAYER]->Info.HP <= 0)	// �÷��̾� HP�� 0�� ���ų� ����, ���� �й�
		{
			printf_s("�������� �й��Ͽ����ϴ�...\n");
			printf_s("����ġ�� %d ��ŭ �Ҿ����ϴ�\n", Objects[ENEMY]->Info.EXP);
			Objects[PLAYER]->Info.EXP -= Objects[ENEMY]->Info.EXP;
		}
		//iChoice = 0;
		printf_s("�ٽ� �����Ͻðڽ��ϱ�?  1. �ٽ� ���� 2. ���� ����\n");
		scanf_s("%d", &iChoice);
		switch (iChoice)
		{
		case 1:
			printf_s("�ٽ� �����ϼ̽��ϴ�. ���ӿ� �����մϴ�\n");	// ���� ���� �ݺ�
			Sleep(500);
			break;
		case 2:
			iLoopC = 0;											// ���� ���� Ż��
			break;
		}

	}
	Sleep(250);
	printf_s("������ �����մϴ�. �����ϼ̽��ϴ�\n");





	return 0;
}

void InitializeObject(OBJECT* _Obj, int ObjectType)		// OBJECT ����ü ������ Ÿ�� ������ int ������ �Ű������� ����ϴ� �Լ� ���Ǻ�
{
	switch (ObjectType)
	{
	case PLAYER:										// ���޹��� ObjectType ���� 0�� ��� (�÷��̾�)
		_Obj->Info.Name = SetName();					// SetName �Լ� ����

		_Obj->Info.Att = 10;							// �÷��̾� ���� ���� (main���� ���� Objects[PLAYER])
		_Obj->Info.Def = 10;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 100;
		_Obj->Info.MP = 10;
		_Obj->Info.Level = 1;
		break;
	case ENEMY:											// 1�� ��� (����)

		_Obj->Info.Name = (char*)"Enemy";

		_Obj->Info.Att = 5;
		_Obj->Info.Def = 5;
		_Obj->Info.EXP = 20;
		_Obj->Info.HP = 30;
		_Obj->Info.MP = 5;
		_Obj->Info.Level = 1;
		break;
	}

	
}


char* SetName()											// �÷��̾��� �̸��� �Է¹ް� char* Ÿ������ ��ȯ�� �Լ�
{
	char Buffer[128] = "";								// �ѱ��� �Է¹ޱ� ���� 128byte �������� ���ڿ� ������ �ʱ�ȭ
	
	printf_s("�̸� �Է� : ");
	scanf("%s", Buffer);								// �Է¹��� %s���� Buffer ���ڿ��� ����

	char* pName = (char*)malloc(strlen(Buffer + 1));	// ���ڿ� �����͸� ����ϱ� ���� ���� �Ҵ�
	strcpy(pName, Buffer);								// Buffer ���ڿ��� �� ���� pName ���ڿ� �����Ϳ� ����

	return pName;										// char* Ÿ�� pName ��ȯ
}


