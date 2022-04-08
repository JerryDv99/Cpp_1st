#include <stdio.h>

int main(void) // main ***
{
	//	[서식문자]
	// 
	//	[%c] = 문자 출력
	//	[%s] = 문자열 출력
	//	[%d] = 정수 출력
	//	[%f] = 실수 출력
	// 
	// sizeof 함수가 (datatype) 사이 자료형의 길이를 byte 단위로 %d(정수)에 반환
	printf_s("char : %d\n", sizeof(char)); 
	printf_s("short : %d\n", sizeof(short));
	printf_s("int : %d\n", sizeof(int));
	printf_s("float : %d\n", sizeof(float));
	printf_s("long : %d\n", sizeof(long));
	printf_s("double : %d\n", sizeof(double));

	printf_s("*************************************\n");
	printf_s("Let's Study C/C++ Game Programming!!!\n");
	printf_s("*************************************\n");
	
	
	return 0;
}