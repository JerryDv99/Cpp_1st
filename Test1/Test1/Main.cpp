#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>


typedef struct sInfo
{
	int HP;
	int MP;

	float ATK;
	float DEF;

	int Level;
	int Speed;

	int EXP;
	int Gold;

} INFO;

typedef struct tagObject
{
	char* Name;
	INFO Info;

} OBJECT;

char* SetName();

void InitializePlayer(OBJECT* _Obj);
void InitializeEnemy1(OBJECT* _Obj);
void InitializeEnemy2(OBJECT* _Obj);
void InitializeEnemy3(OBJECT* _Obj);
void InitializeEnemy4(OBJECT* _Obj);
void InitializeEnemy5(OBJECT* _Obj);


char* StoryScene();

int main(void)
{
	/*OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);*/
	
	StoryScene();

	return 0;
}

char* SetName()
{
	char Buffer[128] = "";

	printf_s("����� �̸���...");
	scanf("%s", Buffer);

	if (strcmp(Buffer, "��浿") == 0)
	{
		printf_s("�׷�, ���� �ٷ� �� ���� ���� ��浿�̴�");
	}
	else
		printf_s("�ƴ�, �Ҿƹ������� �����ֽ� �� �̸��� ��浿�̾�!");

	char* pName = (char*)malloc(7);

	strcpy(pName, "��浿");

	return pName;
}

void SceneManager(OBJECT* Player, OBJECT* Enemy)
{

}

void LogoScene()
{

}

void MainScene()
{

}
char* StoryScene()
{
	char* Story1 = "'��浿 ����'\n";
	char* Story2 = "";


	return 0;
}

void StageScene()
{

}

void InitializePlayer(OBJECT* _Player)
{
	_Player->Name = SetName();

	_Player->Info.HP = 100;
	_Player->Info.MP = 5;
	_Player->Info.ATK = 5;
	_Player->Info.DEF = 5;
	_Player->Info.Level = 1;
	_Player->Info.Speed = 3;
	_Player->Info.EXP = 0;
	_Player->Info.Gold = 5000;

}

void PlayerScene()
{

}


void InitializeEnemy1(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�ֹ��� �˹��ҳ�";

	_Obj->Info.HP = 15;
	_Obj->Info.MP = 0;
	_Obj->Info.ATK = 3;
	_Obj->Info.DEF = 1;
	_Obj->Info.Level = 1;
	_Obj->Info.Speed = 1;
	_Obj->Info.EXP = 100;
	_Obj->Info.Gold = 1000;
}

void InitializeEnemy2(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�ذ� ��ɲ�";

	_Obj->Info.HP = 40;
	_Obj->Info.MP = 0;
	_Obj->Info.ATK = 10;
	_Obj->Info.DEF = 10;
	_Obj->Info.Level = 3;
	_Obj->Info.Speed = 3;
	_Obj->Info.EXP = 300;
	_Obj->Info.Gold = 2000;
}

void InitializeEnemy3(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�渶���� ��X��";

	_Obj->Info.HP = 100;
	_Obj->Info.MP = 5;
	_Obj->Info.ATK = 30;
	_Obj->Info.DEF = 5;
	_Obj->Info.Level = 9;
	_Obj->Info.Speed = 3;
	_Obj->Info.EXP = 1000;
	_Obj->Info.Gold = 10000;
}

void InitializeEnemy4(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�ذ� ŷ";

	_Obj->Info.HP = 15;
	_Obj->Info.MP = 0;
	_Obj->Info.ATK = 3;
	_Obj->Info.DEF = 1;
	_Obj->Info.Level = 1;
	_Obj->Info.Speed = 1;
	_Obj->Info.EXP = 1;
	_Obj->Info.Gold = 1;
}

void InitializeEnemy5(OBJECT* _Obj)
{
	_Obj->Name = (char*)"�μ���ź���� X��";

	_Obj->Info.HP = 2222;
	_Obj->Info.MP = 22;
	_Obj->Info.ATK = 222;
	_Obj->Info.DEF = 22;
	_Obj->Info.Level = 222;
	_Obj->Info.Speed = 22;
	_Obj->Info.EXP = 22222;
	_Obj->Info.Gold = 222222;
}

//void EnemyScene()
//{
//
//}
//
//void SetPosition(int x, int y, char* str, int color)
//{
//
//}
//
//void SetColor()
//{
//
//}
//
//void HideCursor()
//{
//
//}