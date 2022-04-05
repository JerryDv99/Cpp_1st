#include <stdio.h>

// ** 전역변수 선언부
float g_fVariable;
void LocalFcn(void);
// ** 매개 변수는 해당 영역을 벗어날 수 없다

int Input(int _inumber);
char Output(int _inumber);

int main(void)
{
	/*int iMonth;
	printf_s("탄생석! 태어난 달 : ");
	scanf_s("%d", &iMonth);
	printf_s(" 당신의 탄생석은 ");

	switch(iMonth)
	{
	case 1:
		printf_s("가넷");
		break;
	case 2:
		printf_s("자수정");
		break;
	case 3:
		printf_s("아쿠아마린");
		break;
	case 4:
		printf_s("다이아몬드");
		break;
	case 5:
		printf_s("에메랄드");
		break;
	case 6:
		printf_s("진주");
		break;
	case 7:
		printf_s("루비");
		break;
	case 8:
		printf_s("페리도트");
		break;
	case 9:
		printf_s("사파이어");
		break;
	case 10:
		printf_s("오팔");
		break;
	case 11:
		printf_s("토파즈");
		break;
	case 12:
		printf_s("터키석");
		break;
	default:
		printf_s("잘못된 입력");
	}
	
	printf_s(" 입니다.\n");*/

	// ** 변수의 이름이 같다면 해당 영역에 있는 변수가 우선순위가 높음
	/*int val = 10;

	if (val == 10)
	{
		int val = 20;

		printf_s("%d\n", val);
	}

	printf_s("%d\n", val);
	*/
	/*LocalFcn();

	g_fVariable = 3.14f;
	char cMainA = 'A';
	char cMainB = 'B';
	{
		int m_iLocal = 10;
		g_fVariable = 6.28f;
		printf_s("m_iLocal : %d\ng_Variable : %.2f\n\n",
			m_iLocal, g_fVariable);
	}


	printf_s("cMainA : %c\n", cMainA);
	printf_s("cMainB : %c\n", cMainB);
	printf_s("g_Variable : %.2f\n\n", g_fVariable);*/

	int iNumber;
	printf_s("1~255 중 하나 : ");
	scanf_s("%d", &iNumber);

	switch (Input(iNumber))
	{
	case 1:
		printf_s("숫자 1 입력\n\n");
		break;
	case 2:
		printf_s("숫자 2 입력\n\n");
		break;
	case 3:
		printf_s("숫자 3 입력\n\n");
		break;
	default:
		printf_s("%c\n", Output(iNumber));
	}
	
	return 0;	
}

void LocalFcn(void)
{
	int iLocalA = 20;
	int iLocalB = 30;
	g_fVariable = 9.42f;
	printf_s("iLocalA : %d\niLocalB : % d\ng_Variable : % .2f\n\n" ,
		iLocalA, iLocalB, g_fVariable);
}

int Input(int _inumber)
{
	return _inumber;
}

char Output(int _inumber)
{
	return _inumber;
}