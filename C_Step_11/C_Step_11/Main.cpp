#include <stdio.h>
#include <string.h>

int main(void)
{
	/*char cAlphabet;
	char cHanguel;

	cAlphabet = 'A';
	cHanguel = 'วั';

	printf_s("Alphabet : %c / Hanguel : %c\n", cAlphabet, cHanguel);
	char cHarray[] = "วั";
	printf_s("%s\n\n", cHarray);

	printf_s("%d\n\n", sizeof(cHarray));*/

	char* cpArray = (char*)"Character Pointer Array";

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
	printf_s("cpArray[0]	: %c\n\n", cpArray[0]);

	return 0;
}