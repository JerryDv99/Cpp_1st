#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <malloc.h>

//typedef struct tagInfo
//{
//	char* pName;
//	int iKor;
//	int iEng;
//	int iMath;
//}INFO;

typedef struct tagInventory
{
	int iHPotion;
	int iMPotion;

}INVENTORY;

typedef struct tagInfo
{
	int iX;
	int iY;
	INVENTORY* pInventory;
}INFO;

int main(void)
{
	//INFO info;
	/*
	// ** �Է��� ���Ƿ� ������ ����
	char Buffer[128] = "";

	printf_s("�̸� �Է� :");
	// ** �Է��� ����
	scanf("%s", Buffer);

	// ** ������ ������ ���ڿ��� ���̸�ŭ �����Ҵ�
	char* pName = (char*)malloc(strlen(Buffer)+1);

	// ** ���ڿ� ����
	strcpy(pName, Buffer);

	// ���
	printf_s("%s\n", pName);
	*/

	/*printf_s("%d\n", sizeof(INFO*));
	printf_s("%d\n", sizeof(INFO));*/

	/*INFO* pInfo = (INFO*)malloc(sizeof(INFO));

	pInfo->iKor;
	pInfo->iEng;
	pInfo->iMath;

	printf_s("%d\n", pInfo->iKor);
*/

	INFO* pInfo = (INFO*)malloc(sizeof(INFO));
	pInfo->pInventory = (INVENTORY*)malloc(sizeof(INVENTORY));

	pInfo->iX = 10;
	pInfo->iY = 20;
	pInfo->pInventory->iHPotion = 1;
	pInfo->pInventory->iMPotion = 2;

	printf_s("iX : IY = %d : %d\n", pInfo->iX, pInfo->iY);
	printf_s("iHPotion : iMpotion = %d : %d\n",
		pInfo->pInventory->iHPotion, pInfo->pInventory->iMPotion);
	free(pInfo->pInventory);
	free(pInfo);

	return 0;
}