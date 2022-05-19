// Framework v 0.3

// �÷��̾� ���� ������ ����ü �浹

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  // ����� ���
#include <Windows.h>
#include <string>

using namespace std;	// iostream�� ��Ʈ


typedef struct Vector3
{
	int x = 0, y = 0, z = 0;

	Vector3() {};	//	�⺻ ������ ���̴�

	Vector3(int _x, int _y)	// ���� �����ڸ� ���� �� ����
		: x(_x), y(_y), z(0) { };	// ������� �ʴ� ������ �ʱ�ȭ

	Vector3(int _x, int _y, int _z)	// �̸��� ���Ƶ� �Ű������� ���³� ������ ���� �´� �Լ� ȣ��
		: x(_x), y(_y), z(_z) { };


}Vector3;


struct Transform
{
	// ������Ʈ�� �����ϱ� ���� �ʿ��� �ּ����� ��ҵ�
	Vector3 Position;	// ��ǥ
	Vector3 Rotation;	// ȸ����
	Vector3 Scale;		// ũ��
};

struct Information
{
	char* Texture;
	int Color;
	int Option;
};

struct Object
{
	char* Name;
	int Speed;
	Information Info;
	Transform TransInfo;
};

struct DrawTextInfo
{
	Information Info;
	Transform TransInfo;
};

// �ʱ�ȭ �Լ� {����Ʈ �Ű����� : int _Value = 0, ����Ʈ�� �Լ� ���Ǻο��� ��� �Ұ��ϸ� �ڿ������� ä����� ��(_X = 1, _Y, _Z = 3 �ȵ�)}
void Initialize(Object* _Object, char* _Texture, int _PosX = 0, int _PosY = 0, int _PosZ = 0);

// �̸� ���� �Լ�
char* SetName();

// Ŀ���� ��ġ�� ����
void SetCursorPosition(int _x, int _y);

// Text�� ���� ����
void SetTextColor(int _Color);

// ����� Text�� ��ġ�� ������ �������ش� (Color default = ���)
void OnDrawText(char* _str, int _x, int _y, int _Color = 15);

// ����� ������ ��ġ�� ������ �������ش�
void OnDrawText(int _Value, int _x, int _y, int _Color = 15);

// Ŀ���� ��Ÿ���ų�(True) �����(False) �Լ�
void HideCursor(bool _Visible);


int main(void)
{
	
	int Score = 0;

	HideCursor(false); // Ŀ���� ����

	// ��� �ʱ�ȭ
	
	DrawTextInfo BackGround[30];


	for (int i = 0; i < 30; ++i)
	{
		// �������� �ʱ�ȭ ����, ū ���� ���� �� �ֵ��� time������ ������ ��������
		// for���� ������ ���ԵǸ� time�� ���������� ���� �� �ֱ� ������
		// �������̶�� �ϴ��� �������� ���� ���� ���� �� ����
		// i�� ���� ���ϰ� ���������ν� �ߺ����� ������ �ʵ��� ����
		srand((GetTickCount() + i * i)* GetTickCount());


		// ���� ��� ������� ������ �ʾ�����, ���� ���� �Ѿ��� �������� �÷��̾ ���� �������
		// �Ѿ˿� ����� ������ �浹������ �ǵ��� �������� ����
		BackGround[i].Info.Option = 0;

		// ��ǥ�� �������� ����
		BackGround[i].TransInfo.Position.x = rand() % 100 + 10;
		BackGround[i].TransInfo.Position.y = rand() % 26 + 1;

		BackGround[i].Info.Texture = (char*)"*";

		BackGround[i].Info.Color = rand() % 8 + 1;

	}



	// ** �÷��̾� ���� �� �����Ҵ�
	Object* Player = new Object;

	// ** �÷��̾� �ʱ�ȭ
	Initialize(Player, (char*)"��/", 30, 10);

	Object* Enemy = new Object;
	Initialize(Enemy, (char*)"Ȫ", 80, 10);

	// ���� �ð����� �ʱ�ȭ
	ULONGLONG Time = GetTickCount64();

	// ���
	while (true)
	{
		// �ʱ�ȭ�� �ð����� +50��ŭ �����ϸ�
		// �����Ӱ� ������ ������ �ð� ������ 0.5�ʷ� ����
		if (Time + 80 < GetTickCount64())
		{
			// ������ ����ŭ �ٽ� �ʱ�ȭ
			Time = GetTickCount64();

			system("cls");

			// ** ��� ���
			for (int i = 0; i < 30; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);

				// ** ������� ���� �ؽ�ó�� ������ �������� ����.
				BackGround[i].Info.Color = rand() % 8 + 1;
			}

			// �� Ű�� �Է¹���
			if (GetAsyncKeyState(VK_UP))
			{
				Player->TransInfo.Position.y -= 1;
			}

			// �� Ű�� �Է¹���
			if (GetAsyncKeyState(VK_DOWN))
			{
				Player->TransInfo.Position.y += 1;
			}

			// �� Ű�� �Է¹���
			if (GetAsyncKeyState(VK_LEFT))
			{
				Player->TransInfo.Position.x -= 1;
			}

			// �� Ű�� �Է¹���
			if (GetAsyncKeyState(VK_RIGHT))
			{
				Player->TransInfo.Position.x += 1;
			}
			
			// �����̽� Ű�� �Է¹���
			if (GetAsyncKeyState(VK_SPACE))
				Player->Info.Texture = (char*)"�ʤ�";
			else
				Player->Info.Texture = (char*)"��/";

			OnDrawText(Enemy->Info.Texture,
				Enemy->TransInfo.Position.x,
				Enemy->TransInfo.Position.y,
				12);

			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);

			OnDrawText((char*)"Score : ", 60 - strlen("Score : "), 1);
			OnDrawText(++Score, 60, 1);


		}
	}

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

void Initialize(Object* _Object, char* _Texture, int _PosX, int _PosY, int _PosZ)
{
	// ** 3�� ������
	// _Texture�� ���� nullptr�̸� SetName()�Լ� ����
	// �ƴ϶�� _Texture �� ����
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;

	_Object->Speed = 0;

	// ** ��ǥ��
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** ȸ���� (���� ��� ����)
	_Object->TransInfo.Rotation = Vector3(0, 0, 0);

	// ** ũ�Ⱚ
	_Object->TransInfo.Scale = Vector3(0, 0, 0);

}

void SetCursorPosition(int _x, int _y)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetTextColor(int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void OnDrawText(char* _str, int _x, int _y, int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);
	cout << _str;
}

void OnDrawText(int _Value, int _x, int _y, int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	char* pText = new char[4];
	_itoa(_Value, pText, 10);

	cout << _Value;
}

void HideCursor(bool _Visible)
{
	CONSOLE_CURSOR_INFO CursorInfo;

	CursorInfo.bVisible = _Visible;
	CursorInfo.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
