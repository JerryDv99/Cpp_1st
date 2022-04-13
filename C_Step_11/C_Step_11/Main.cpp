#include <stdio.h>
#include <string>
#include <time.h>

//char* SetName()
//{
//	char Buffer[128] = "";
//
//	printf_s("당신의 이름을 입력하세요.\n");
//	printf_s("입력\n");
//
//	
//	scanf("%s", Buffer);
//
//	char* pName = (char*)malloc(strlen(Buffer) + 1);
//
//	strcpy(pName, Buffer);
//
//	return pName;
//}


int main(void)
{
	/*char Buffer[128] = "";
	char* pName = SetName();*/

	
	/*char cAlphabet;
	char cHanguel;

	cAlphabet = 'A';
	cHanguel = '한';

	printf_s("Alphabet : %c / Hanguel : %c\n", cAlphabet, cHanguel);
	char cHarray[] = "한";
	printf_s("%s\n\n", cHarray);

	printf_s("%d\n\n", sizeof(cHarray));*/

	/*char* cpArray = (char*)"Character Pointer Array";

	printf_s("&cpArray		: %d\n", &cpArray);
	printf_s("cpArray		: %d\n", cpArray);
	printf_s("&cpArray		: %d\n", cpArray[0]);
	printf_s("cpArray		: %s\n\n", cpArray);

	printf_s("*cpArray		: %c\n", *cpArray);
	printf_s("cpArray[0]	: %c\n", cpArray[0]);
	printf_s("cpArray[1]	: %c\n\n", cpArray[1]);

	printf_s("*cpArray++	: %c\n", *cpArray++);
	printf_s("cpArray		: %s\n", cpArray);
	printf_s("*cpArray--	: %c\n", *cpArray--);
	printf_s("cpArray		: %s\n\n", cpArray);

	printf_s("cpArray		: %d\n", cpArray);
	printf_s("*cpArray		: %c\n", *cpArray);
	cpArray++;
	printf_s("cpArray		: %d\n", cpArray);
	printf_s("cpArray[0]	: %c\n\n", cpArray[0]);*/

	// **랜덤 함수 초기화
	srand(time(NULL));


	printf_s("로또번호 추첨\n");
	printf_s("===========================\n");
	for (int i = 0; i < 6; i++)
	{
		int j = rand() % 99 + 1; // 랜덤 함수
		printf_s(" %d ", j);
	}
	printf_s("\n");
	printf_s("===========================\n");


	const int Max = 7;

	int Numbers[8];

	time_t tTime = time(NULL);
	int i = 0;

	while (true)
	{
		if (tTime < time(NULL))
		{
			tTime = time(NULL);

			srand(time(NULL));
			Numbers[i] = rand() % 45 + 1;

			//printf_s("%d  ", Numbers[i]);

			i++;

			if (i >= 6)
				break;
		}
	}
	
	for (int i = 0; i < 6; i++)
		printf_s("%d ", Numbers[i]);

	printf_s("\n");


	return 0;
}