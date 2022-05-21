#pragma once
// �Լ� ����

// �ʱ�ȭ �Լ� {����Ʈ �Ű����� : int _Value = 0, ����Ʈ�� �Լ� ���Ǻο��� ��� �Ұ��ϸ� �ڿ������� ä����� ��(_X = 1, _Y, _Z = 3 �ȵ�)}
void Initialize(Object* _Object, char* _Texture, float _PosX = 0, float _PosY = 0, float _PosZ = 0);

// �̸� ���� �Լ�
char* SetName();

// Ŀ���� ��ġ�� ����
void SetCursorPosition(const float _x, const float _y);

// Text�� ���� ����
void SetTextColor(const int _Color);

// ����� Text�� ��ġ�� ������ �������ش� (Color default = ���)
void OnDrawText(const char* _str, const float _x, const float _y, const int _Color = 15);

// ����� ������ ��ġ�� ������ �������ش�
void OnDrawText(const int _Value, const float _x, const float _y, const int _Color = 15);

// Ŀ���� ��Ÿ���ų�(True) �����(False) �Լ�
void HideCursor(const bool _Visible);

// �浹ó�� �Լ�
bool Collision(const Object* _ObjectA, const Object* _ObjectB);

// Bullet �����Լ�
Object* CreateBullet(const float _x, const float _y);

Object* CreateEnemy(const float _x, const float _y);

// Ű �Է�
void UpdateInput(Object* _Object);


void Initialize(Object* _Object, char* _Texture, float _PosX, float _PosY, float _PosZ)
{
	// ** 3�� ������
	// _Texture�� ���� nullptr�̸� SetName()�Լ� ����
	// �ƴ϶�� _Texture �� ����
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;

	_Object->Speed = 0;

	// ** ��ǥ��
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** ȸ���� (���� ��� ����)
	_Object->TransInfo.Rotation = Vector3(0.0f, 0.0f, 0.0f);

	// ** ũ�Ⱚ
	_Object->TransInfo.Scale = Vector3((float)strlen(_Object->Info.Texture), 1.0f, 0.0f);

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

void SetCursorPosition(const float _x, const float _y)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetTextColor(const int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void OnDrawText(const char* _str, const float _x, const float _y, const int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);
	cout << _str;
}

void OnDrawText(const int _Value, const float _x, const float _y, const int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	char* pText = new char[4];
	_itoa(_Value, pText, 10);

	cout << _Value;
}

void HideCursor(const bool _Visible)
{
	CONSOLE_CURSOR_INFO CursorInfo;

	CursorInfo.bVisible = _Visible;
	CursorInfo.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}

bool Collision(const Object* _ObjectA, const Object* _ObjectB)
{
	// Position.x + Scale.x = ����
	// Position.x = ����
	// Rect �浹 �� �������� �׻� ũ��
	if ((_ObjectA->TransInfo.Position.x + _ObjectA->TransInfo.Scale.x) > _ObjectB->TransInfo.Position.x &&
		(_ObjectB->TransInfo.Position.x + _ObjectB->TransInfo.Scale.x) > _ObjectA->TransInfo.Position.x &&
		_ObjectA->TransInfo.Position.y == _ObjectB->TransInfo.Position.y)
		return true;
	 return false;
}

Object* CreateBullet(const float _x, const float _y)
{
	// Bullet ���� �� �����Ҵ�
	Object* _Object = new Object;

	// ������ ���� �ʱ�ȭ �� _x�� _y�� ������ �� ���� ����� �޾ƿ�
	Initialize(_Object, (char*)"==", _x + 2, _y);

	return _Object;
}

Object* CreateEnemy(const float _x, const float _y)
{
	Object* _Object = new Object;

	Initialize(_Object, (char*)"-<=", _x, _y);

	return _Object;
}

void UpdateInput(Object* _Object)
{
	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_UP))
		_Object->TransInfo.Position.y -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_DOWN))
		_Object->TransInfo.Position.y += 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_LEFT))
		_Object->TransInfo.Position.x -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_RIGHT))
		_Object->TransInfo.Position.x += 1;
}
