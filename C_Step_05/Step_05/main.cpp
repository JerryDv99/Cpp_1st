#include <stdio.h>

// ** �������� �����
float g_fVariable;
void LocalFcn(void);
// ** �Ű� ������ �ش� ������ ��� �� ����

int Input(int _inumber);
char Output(int _inumber);

int main(void)
{
	/*int iMonth;
	printf_s("ź����! �¾ �� : ");
	scanf_s("%d", &iMonth);
	printf_s(" ����� ź������ ");

	switch(iMonth)
	{
	case 1:
		printf_s("����");
		break;
	case 2:
		printf_s("�ڼ���");
		break;
	case 3:
		printf_s("����Ƹ���");
		break;
	case 4:
		printf_s("���̾Ƹ��");
		break;
	case 5:
		printf_s("���޶���");
		break;
	case 6:
		printf_s("����");
		break;
	case 7:
		printf_s("���");
		break;
	case 8:
		printf_s("�丮��Ʈ");
		break;
	case 9:
		printf_s("�����̾�");
		break;
	case 10:
		printf_s("����");
		break;
	case 11:
		printf_s("������");
		break;
	case 12:
		printf_s("��Ű��");
		break;
	default:
		printf_s("�߸��� �Է�");
	}
	
	printf_s(" �Դϴ�.\n");*/

	// ** ������ �̸��� ���ٸ� �ش� ������ �ִ� ������ �켱������ ����
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
	printf_s("1~255 �� �ϳ� : ");
	scanf_s("%d", &iNumber);

	switch (Input(iNumber))
	{
	case 1:
		printf_s("���� 1 �Է�\n\n");
		break;
	case 2:
		printf_s("���� 2 �Է�\n\n");
		break;
	case 3:
		printf_s("���� 3 �Է�\n\n");
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