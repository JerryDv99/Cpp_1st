#include <stdio.h>

// 0�̸� false, ** 0�� �ƴ� ���� True

int main(void)
{
	/*
	int i = 0;	
	printf_s("1. �� ��\n");
	printf_s("2. �� ��\n");
	printf_s("�Է� : ");
	scanf_s("%d", &i);

	if (i == 1)	// if ���� �б��� �������� ������ if�� ���������� �� else�� ���� �ʿ�� ����
	{
		printf_s("��縦 ���� �Ͽ����ϴ�.\n");
	}
	else if (i == 2)
	{
		printf_s("�ü��� ���� �Ͽ����ϴ�.\n");
	}
	else if (i != 1)	// else
	{
		printf_s("�߸� �Է� �ϼ̽��ϴ�.\n");
	}
	// if() {	} ���� �б��� ����
	*/

	float weight = 0;
	float height = 0;
	

	printf_s("Ű�� �Է��ϼ��� : (m)");
	scanf_s("%f", &height);
	printf("\n");

	printf_s("�����Ը� �Է��ϼ��� : (kg)");
	scanf_s("%f", &weight);
	
	float BMI = weight / (height * height);

	if (BMI < 18.5)	// if �� �Ʒ��� 1�ٱ����� �߰�ȣ ���̵� if �������� ���
	{
		printf_s("����� �� ������ ü�߹̴� �Դϴ�\n");		
	}
	else if (BMI <= 22.9)
	{
		printf_s("����� �� ������ ǥ�� �Դϴ�\n");		
	}
	else if (BMI <= 24.9)
	{
		printf_s("����� �� ������ ��ü�� �Դϴ�\n");
	}
	else if (BMI <=29.9)
	{
		printf_s("����� �� ������ �� �Դϴ�\n");
	}
	else
	{
		printf_s("����� �� ������ ���� �Դϴ�\n");
	}

	/*
	int iHeight;
	int iWeight;
	float fHeight;
	float fBmi;
	printf_s(��Ű (cm) : ��); 
	scanf_s(��%d��, &iHeight);
	printf_s(�������� (kg) : ��);
	scanf_s(��%d��, &iWeight);
	
	fHeight = iHeight / 100.0f;
	fBmi = iWeight / (fHeight * fHeight);
	printf_s(�������� : %.1f��, fBmi);

	if (fBmi >= 30)
	     printf_s(������\n��);

	else if(fBmi >= 25)
	     printf_s(����\n��);

	else if(fBmi >= 23)
	     printf_s(����ü��\n��);

	else if(fBmi >= 18.5)
	     printf_s(��ǥ��\n��);

	else
	     printf_s(��ü�� �̴�\n��);
	*/

															 
	return 0;
}