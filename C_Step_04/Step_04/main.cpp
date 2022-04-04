#include <stdio.h>

// 0이면 false, ** 0이 아닌 값은 True

int main(void)
{
	/*
	int i = 0;	
	printf_s("1. 기 사\n");
	printf_s("2. 궁 수\n");
	printf_s("입력 : ");
	scanf_s("%d", &i);

	if (i == 1)	// if 문은 분기의 시작으로 무조건 if로 시작하지만 꼭 else로 끝날 필요는 없음
	{
		printf_s("기사를 선택 하였습니다.\n");
	}
	else if (i == 2)
	{
		printf_s("궁수를 선택 하였습니다.\n");
	}
	else if (i != 1)	// else
	{
		printf_s("잘못 입력 하셨습니다.\n");
	}
	// if() {	} 다음 분기의 시작
	*/

	float weight = 0;
	float height = 0;
	

	printf_s("키를 입력하세요 : (m)");
	scanf_s("%f", &height);
	printf("\n");

	printf_s("몸무게를 입력하세요 : (kg)");
	scanf_s("%f", &weight);
	
	float BMI = weight / (height * height);

	if (BMI < 18.5)	// if 문 아래로 1줄까지는 중괄호 없이도 if 구문으로 취급
	{
		printf_s("당신의 비만 지수는 체중미달 입니다\n");		
	}
	else if (BMI <= 22.9)
	{
		printf_s("당신의 비만 지수는 표준 입니다\n");		
	}
	else if (BMI <= 24.9)
	{
		printf_s("당신의 비만 지수는 과체중 입니다\n");
	}
	else if (BMI <=29.9)
	{
		printf_s("당신의 비만 지수는 비만 입니다\n");
	}
	else
	{
		printf_s("당신의 비만 지수는 고도비만 입니다\n");
	}

	/*
	int iHeight;
	int iWeight;
	float fHeight;
	float fBmi;
	printf_s(“키 (cm) : ”); 
	scanf_s(“%d”, &iHeight);
	printf_s(“몸무게 (kg) : ”);
	scanf_s(“%d”, &iWeight);
	
	fHeight = iHeight / 100.0f;
	fBmi = iWeight / (fHeight * fHeight);
	printf_s(“비만지수 : %.1f”, fBmi);

	if (fBmi >= 30)
	     printf_s(“고도비만\n”);

	else if(fBmi >= 25)
	     printf_s(“비만\n”);

	else if(fBmi >= 23)
	     printf_s(“과체중\n”);

	else if(fBmi >= 18.5)
	     printf_s(“표준\n”);

	else
	     printf_s(“체중 미달\n”);
	*/

															 
	return 0;
}