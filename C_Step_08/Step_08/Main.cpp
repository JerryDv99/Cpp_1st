#include <stdio.h>

int main(void)
{
	// ������ �ּҰ��� %p�� %d ������ ���
	
	/*int iNumber = 19;
	int* piNumber;
	piNumber = &iNumber;

	printf_s("iNumber	: %d\n", iNumber);		
	printf_s("*piNumber : %d\n", *piNumber);	// �����ͷ� ������ iNumber ��
	printf_s("piNumber	: %d\n", piNumber);		// �����Ͱ� �����ִ� iNumber �ּ�
	printf_s("&iNumber	: %d\n", &iNumber);		// iNumber �ּҰ�
	printf_s("&piNumber	: %d\n\n", &piNumber);	// ������ ��ü�� �ּҰ�
	*/

	// ** [������ ��� ��� 3����]
	// ** 1. [*] = ������ , [&] = �ּ�
	// ** 2. ������ ������� ������ �����Ҵ��� ���ֵ��� �Ѵ�
	// ** 3. [.] �ƴϸ� [->] ȭ��ǥ

	int iNumber1 = 19;
	int iNumber2 = iNumber1;

	int* pPointer1 = &iNumber1;
	int* pPointer2 = &iNumber2;

	printf_s("pPointer1 : %d\n", *pPointer1);
	iNumber1 = 100;
	printf_s("pPointer2 : %d\n", *pPointer2);


	return 0;
}