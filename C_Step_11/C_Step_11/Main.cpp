#include <stdio.h>
#include <string>
#include <time.h>

//char* SetName()
//{
//	char Buffer[128] = "";
//
//	printf_s("����� �̸��� �Է��ϼ���.\n");
//	printf_s("�Է�\n");
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
	cHanguel = '��';

	printf_s("Alphabet : %c / Hanguel : %c\n", cAlphabet, cHanguel);
	char cHarray[] = "��";
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

	// **���� �Լ� �ʱ�ȭ
	srand(time(NULL));


	printf_s("�ζǹ�ȣ ��÷\n");
	printf_s("===========================\n");
	for (int i = 0; i < 6; i++)
	{
		int j = rand() % 99 + 1; // ���� �Լ�
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