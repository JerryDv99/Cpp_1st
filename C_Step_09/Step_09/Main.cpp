#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>


//typedef struct tagInfo
//{
//	char Name[7];
//
//	int iKor;
//	int iEng;
//	int iMath;
//}INFO;


typedef struct statInfo
{
	int iProfession;
	int iAtt;
	int iDef;
	int iSpeed;
	int iHealth;
	int iMagic;
	int iGold;
}SINFO;

SINFO Initialize(void);
SINFO MonsterInitialize(void);
void ProfessionSetting(SINFO* _info);
void StatusSetting(SINFO* _info, int _profession);
void StatusOutput(SINFO _info, int _index);

int main(void)
{
	/*tagInfo StudentA;
	tagInfo StudentB;

	printf_s("StudentA : \n");
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentA.iKor);
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentA.iEng);
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentA.iMath);
	printf_s("�� : %d, �� : %d, �� : %d\n",
		StudentA.iKor, StudentA.iEng, StudentA.iMath);

	printf_s("StudentB : \n");
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentB.iKor);
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentB.iEng);
	printf_s("���� ���� : ");
	scanf_s("%d", &StudentB.iMath);
	printf_s("�� : %d, �� : %d, �� : %d\n",
		StudentB.iKor, StudentB.iEng, StudentB.iMath);*/

	/*INFO info;
	int iIndex = 0;

	printf_s("����� ������ ���� �Դϱ�??\n");
	printf_s("***************************\n");
	printf_s("*     1. ��      ��       *\n");
	printf_s("*     2. ��  ��  ��       *\n");
	printf_s("*     3. ��      ��       *\n");
	printf_s("***************************\n");
	scanf_s("%d", &iIndex);

	switch (iIndex)
	{
	case 1:
		strcpy(info.Name, "����");
		break;

	case 2:
		strcpy(info.Name, "������");
		break;

	case 3: 
		strcpy(info.Name, "����");
		break;
	}

	printf_s("%s\n", info.Name);*/

	

	/*INFO Student[3];

	printf_s("ù ��° �л�\n");
	printf_s("�̸� : ��浿\n");
	strcpy(Student[0].Name, "��浿");
	printf_s("���� ���� : ");
	scanf_s("%d", &Student[0].iKor);
	printf_s("���� ���� : ");
	scanf_s("%d", &Student[0].iEng);
	printf_s("���� ���� : ");
	scanf_s("%d", &Student[0].iMath);
	printf_s("�̸� : ��浿, ���� ���� : %d, ���� ���� : %d, ���� ���� : %d\n",
		Student[0].iKor, Student[0].iEng, Student[0].iMath);

	printf_s("�� ��° �л�\n");
	printf_s("�̸� : ȫų��\n");
	strcpy(Student[1].Name, "ȫų��");
	printf_s("���� ���� : ");
	scanf_s("%d", &Student[1].iKor);
	printf_s("���� ���� : ");
	scanf_s("%d", &Student[1].iEng);
	printf_s("���� ���� : ");
	scanf_s("%d", &Student[1].iMath);
	printf_s("�̸� : ȫų��, ���� ���� : %d, ���� ���� : %d, ���� ���� : %d\n",
		 Student[1].iKor, Student[1].iEng, Student[1].iMath);

	printf_s("�� ��° �л�\n");
	printf_s("�̸� : ����\n");
	strcpy(Student[2].Name, "����");
	printf_s("���� ���� : ");
	scanf_s("%d", &Student[2].iKor);
	printf_s("���� ���� : ");
	scanf_s("%d", &Student[2].iEng);
	printf_s("���� ���� : ");
	scanf_s("%d", &Student[2].iMath);
	printf_s("�̸� : ����, ���� ���� : %d, ���� ���� : %d, ���� ���� : %d\n",
		Student[2].iKor, Student[2].iEng, Student[2].iMath);*/

	int iPlayerIndex = 0;
	SINFO Player = Initialize();
	SINFO Monster[3];

	ProfessionSetting(&Player);
	StatusOutput(Player, iPlayerIndex);

	for (int i = 0; i < 3; i++)
	{
		Monster[i] = MonsterInitialize();
		StatusOutput(Monster[i],i);
	}




	return 0;
}

SINFO Initialize(void)
{
	SINFO _info;

	_info.iProfession = 0;
	_info.iAtt = 0;
	_info.iDef = 0;
	_info.iSpeed = 0;
	_info.iHealth = 0;
	_info.iMagic = 0;
	_info.iGold = 100;

	return _info;
}

SINFO MonsterInitialize(void)
{
	SINFO _info;

	_info.iProfession = 4;
	_info.iAtt = 7;
	_info.iDef = 4;
	_info.iSpeed = 3;
	_info.iHealth = 100;
	_info.iMagic = 30;
	_info.iGold = 10;

	return _info;
}

void ProfessionSetting(SINFO* _info)
{
	int iIndex = 0;
	printf_s("����� ������ ���� �Դϱ�??\n");
	printf_s("***************************\n");
	printf_s("*     1. ��      ��       *\n");
	printf_s("*     2. ��  ��  ��       *\n");
	printf_s("*     3. ��      ��       *\n");
	printf_s("***************************\n");
	scanf_s("%d", &iIndex);
	switch (iIndex)
	{
	case 1:
		_info->iProfession = 1;
		break;
	case 2:
		_info->iProfession = 2;
		break;
	case 3:
		_info->iProfession = 3;
		break;
	}
	StatusSetting(_info, _info->iProfession);
}

void StatusSetting(SINFO* _info, int _profession)
{
	_info->iAtt = (_profession % 2) * _profession * 2 + 5;
	_info->iDef = (_profession % 2) * _profession * 2 + 3;
	_info->iSpeed = (_profession - 3) * 3 + 3;
	_info->iHealth = (_profession % 2) * _profession * 30 + 50;

	if (_profession == 2)
	{
		_info->iMagic = 200;
	}
	else
	{
		_info->iMagic = 50;
	}
}

void StatusOutput(SINFO _info, int _index)
{
	if (_info.iProfession == 4)
	{
		printf_s("	����[%d]�� ����\n", _index + 1);
		printf_s("------------------\n");
	}
	else
	{
		printf_s("	�÷��̾� ����\n");
		printf_s("-------------------\n");
	}

	printf_s("	HP	:  %d\n", _info.iHealth);
	printf_s("	MP	:  %d\n", _info.iMagic);
	printf_s("	Att	:  %d\n", _info.iAtt);
	printf_s("	Def	:  %d\n", _info.iDef);
	printf_s("	Speed :  %d\n", _info.iSpeed);
	printf_s("	Gold	: %d\n", _info.iGold);
	printf_s("\n");
}