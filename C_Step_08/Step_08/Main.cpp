#include <stdio.h>

int main(void)
{
	// 포인터 주소값은 %p나 %d 형으로 출력
	
	/*int iNumber = 19;
	int* piNumber;
	piNumber = &iNumber;

	printf_s("iNumber	: %d\n", iNumber);		
	printf_s("*piNumber : %d\n", *piNumber);	// 포인터로 접근한 iNumber 값
	printf_s("piNumber	: %d\n", piNumber);		// 포인터가 갖고있는 iNumber 주소
	printf_s("&iNumber	: %d\n", &iNumber);		// iNumber 주소값
	printf_s("&piNumber	: %d\n\n", &piNumber);	// 포인터 자체의 주소값
	*/

	// ** [포인터 사용 방법 3가지]
	// ** 1. [*] = 데이터 , [&] = 주소
	// ** 2. 포인터 변수라면 무조건 동적할당을 해주도록 한다
	// ** 3. [.] 아니면 [->] 화살표

	int iNumber1 = 19;
	int iNumber2 = iNumber1;

	int* pPointer1 = &iNumber1;
	int* pPointer2 = &iNumber2;

	printf_s("pPointer1 : %d\n", *pPointer1);
	iNumber1 = 100;
	printf_s("pPointer2 : %d\n", *pPointer2);


	return 0;
}