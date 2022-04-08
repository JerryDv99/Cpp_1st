#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	/*int i = 0;
	while (i < 10)
	{
		printf_s("Hello World! %d \n", i);
		i++;
	}*/

	/*int iFahrenheit, iCelsius = 0;
	int iLower, iUpper, iStep;

	iLower = 0;
	iUpper = 300;
	iStep = 20;

	iFahrenheit = iLower;

	while (iFahrenheit <= iUpper)
	{
		iCelsius = 5 * (iFahrenheit - 32) / 9;
		printf_s("È­¾¾ : %d\t¼·¾¾ : %d\n", iFahrenheit, iCelsius);
		iFahrenheit += iStep;
	}

	printf_s("\n");*/
	
	/*int iNumber1 = 0;
	int iNumber2 = 0;
	int iNumber3 = 0;
	int iNumber4 = 0;
	int iNumber5 = 0;
	int iCount = 0;
	while (true)
	{
		iCount++;
		printf_s("%d\n", iCount);
		system("cls");
		if (iNumber1 == 0 || iNumber2 == 0 || iNumber3 == 0 || iNumber4 == 0 || iNumber5 == 0)
		{
			if (iCount == 80 && iNumber1 == 0)
			{
				iNumber1 = iCount;
				iCount = 0;
				continue;
			}
			else if (iCount == 90 && iNumber2 == 0)
			{
				iNumber2 = iCount;
				iCount = 0;
				continue;
			}
			else if (iCount == 97 && iNumber3 == 0)
			{
				iNumber3 = iCount;
				iCount = 0;
				continue;
			}
			else if (iCount == 99 && iNumber4 == 0)
			{
				iNumber4 = iCount;
				iCount = 0;
				continue;
			}
			else if (iCount == 101 && iNumber5 == 0)
			{
				iNumber5 = iCount;
				iCount = 0;
				continue;
			}
			else
			{
				printf_s("%c %c %c %c %c\n", iNumber1, iNumber2, iNumber3, iNumber4, iNumber5);
			}
		}
	}*/

	//for (int i = 0; i < 10; i++) // for (ÃÊ±â¹®; Á¶°Ç¹®; Áõ°¨¹®)
	//{
	//	printf_s("Loop Count! : %d\n", i);
	//}

	/*
	for (int i = 2; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			printf_s(" %d x %d = %d\n", i, j, i * j);
		}
		printf_s("\n");
	}
	printf_s("\n");
	*/

	/*int year;
	double d = 24.0f;
	
	for (year = 1627; year < 2018; year++)
	{
		d *= 1.08;
	}
	printf_s("2018 ³â %lf ´Þ·¯\n", d);*/

	for (int i = 0; i < 10; i += 1)
	{
	printf_s("Hello%d\n",i);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10 - i; j++)
		{
			printf_s(" ");
		}
		for (int j = 0; j < 2*i+1 ; j++)
		{
			printf_s("*");
		}
		printf_s("\n");
	}
	for (int k = 0; k < 10; k++)
	{
		for (int m = 0; m <= k + 1; m++)
		{
			printf_s(" ");
		}
		for (int n = 15; n >= 2*k-1; n--)
		{
			printf_s("*");
		}
		printf_s("\n"); 
	}


	return 0;
}