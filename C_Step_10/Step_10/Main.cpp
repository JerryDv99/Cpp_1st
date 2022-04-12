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
	// ** 입력을 임의로 저장할 공간
	char Buffer[128] = "";

	printf_s("이름 입력 :");
	// ** 입력을 받음
	scanf("%s", Buffer);

	// ** 포인터 변수에 문자열의 길이만큼 동적할당
	char* pName = (char*)malloc(strlen(Buffer)+1);

	// ** 문자열 복사
	strcpy(pName, Buffer);

	// 출력
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