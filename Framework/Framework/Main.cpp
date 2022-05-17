// Framework v 0.2

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  // ����� ���
#include <string>

using namespace std;	// iostream�� ��Ʈ

//typedef struct tagInfo
//{
//	int iNumber;
//
//
//	tagInfo()	// ������, ����ü �ȿ����� ��� ����
//	{
//		cout << "�⺻ ������" << endl;	// �ʱ�ȭ �� ������ ȣ��
//	};
//
//	tagInfo(int _iNumber)	
//	{
//		iNumber = _iNumber;
//		cout << "���� ������" << endl;	// �ʱ�ȭ �� ������ ȣ��
//	};
//
//
//}INFO;


typedef struct Vector3
{
	int x = 0, y = 0, z = 0;

	Vector3() {};	//	�⺻ ������ ���̴�

	Vector3(int _x, int _y)	// ���� �����ڸ� ���� �� ����
		: x(_x), y(_y), z(0) { };

	Vector3(int _x, int _y, int _z)	
		: x(_x), y(_y), z(_z) { };


}Vector3;


struct Transform
{
	// ������Ʈ�� �����ϱ� ���� �ʿ��� �ּ����� ��ҵ�
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;
};

struct Object
{
	char* Name;
	int Speed;
	Transform TramsInfo;

};

// �ʱ�ȭ �Լ�
void Initialize(Object* _Object, char* _Name, int _PosX = 0, int _PosY = 0, int _PosZ = 0);

// �̸� ���� �Լ�
char* SetName();

// ��� �Լ�
void Output(Object* _Object);



int main(void)
{
	// ** ���
	//printf_s("���� ���");
	//cout << "���� ���";		// console out <<(����Ʈ ������) "���ڿ�"		
	
	//���� ��������  << ������, >> �ޱ�


	// ** �ٹٲ�
	//printf_s("\\n�� ����ϸ� \n�ٹٲ�");
	//cout << "endl �� ����ϸ�" << endl << "�ٹٲ�";


	/*
	// ** �Է�
	int iNumber = 0;

	
	printf_s("�Է�: ");
	scanf("%d", &iNumber);

	printf_s("��� : %d", iNumber);

	cout << "�Է�: ";
	cin >> iNumber;

	cout << "��� : " << iNumber;
	*/

	// ** �����Ҵ� 
	//INFO* pInfo = (INFO*)malloc(sizeof(INFO));		// malloc�� ���°� void* �̱� ������ ����ȯ
	//INFO* pInfo = new INFO;	// new�� �����Ҵ�, new ���� INFO�� size �� ����
	//INFO* pInfo = new INFO(10);
	//cout << pInfo->iNumber << endl;


	//free(pInfo);
	//delete pInfo;

	/*INFO* pInfo[10];

	for (int i = 0; i < 10; ++i)
	{
		pInfo[i] = new INFO(i);
		cout << pInfo[i]->iNumber << endl;
	}*/

	//for (int i = 0; i < 10; ++i)
		//cout << pInfo[i]->iNumber << endl;

	//Vector3 vPosition = Vector3(10, 20, 30);	// �Ű������� ������ ���¿� ���� ȣ��

	//cout << vPosition.x << ", " << vPosition.y << endl;

	// ** �÷��̾� ���� �� �����Ҵ�
	Object* Player = new Object;

	// ** �÷��̾� �ʱ�ȭ
	Initialize(Player, nullptr, 10, 20, 30);

	Object* Enemy = new Object;
	Initialize(Enemy, (char*)"Enemy", 100, 200, 300);

	Output(Player);
	Output(Enemy);

	return 0;
}

char* SetName()
{
	// ������ �������� �ٷ� �Է¹��� �� ���� ������ ���ڿ��� �Է� ���� �ӽ� ������ �迭�� ���� 
	char Buffer[128] = "";
	
	cout << "�Է� : "; cin >> Buffer;

	// ������ ������ �����Ͽ� �Է¹��� ���ڿ��� ���� + null ��ŭ�� ũ�⸦ �Ҵ�
	//char* pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	// �Է¹��� ���ڿ��� ���� ����
	strcpy(pName, Buffer);

	// char* ��ȯ
	return pName;
}

void Initialize(Object* _Object, char* _Name, int _PosX, int _PosY, int _PosZ)
{
	// ** 3�� ������
	// _Name�� ���� nullptr�̸� SetName()�Լ� ����
	// �ƴ϶�� _Name �� ����
	_Object->Name = (_Name == nullptr) ? SetName() : _Name;

	_Object->Speed = 0;

	// ** ��ǥ��
	_Object->TramsInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** ȸ���� (���� ��� ����)
	_Object->TramsInfo.Rotation = Vector3(0, 0, 0);

	// ** ũ�Ⱚ
	_Object->TramsInfo.Scale = Vector3(0, 0, 0);

}
void Output(Object* _Object)
{
	if (_Object->Name != nullptr)
		cout << "Name : " << _Object->Name << endl;

	cout << "Speed : " << _Object->Speed << endl;

	cout << "X : " << _Object->TramsInfo.Position.x <<
		", Y : " << _Object->TramsInfo.Position.y <<
		", Z : " << _Object->TramsInfo.Position.z << endl;

}
