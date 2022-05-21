#pragma once
// 함수 관리

// 초기화 함수 {디폴트 매개변수 : int _Value = 0, 디폴트는 함수 정의부에서 사용 불가하며 뒤에서부터 채워줘야 함(_X = 1, _Y, _Z = 3 안됨)}
void Initialize(Object* _Object, char* _Texture, float _PosX = 0, float _PosY = 0, float _PosZ = 0);

// 이름 세팅 함수
char* SetName();

// 커서의 위치를 변경
void SetCursorPosition(const float _x, const float _y);

// Text의 색을 변경
void SetTextColor(const int _Color);

// 출력할 Text의 위치와 색상을 변경해준다 (Color default = 흰색)
void OnDrawText(const char* _str, const float _x, const float _y, const int _Color = 15);

// 출력할 숫자의 위치와 색상을 변경해준다
void OnDrawText(const int _Value, const float _x, const float _y, const int _Color = 15);

// 커서를 나타내거나(True) 숨기는(False) 함수
void HideCursor(const bool _Visible);

// 충돌처리 함수
bool Collision(const Object* _ObjectA, const Object* _ObjectB);

// Bullet 생성함수
Object* CreateBullet(const float _x, const float _y);

Object* CreateEnemy(const float _x, const float _y);

// 키 입력
void UpdateInput(Object* _Object);


void Initialize(Object* _Object, char* _Texture, float _PosX, float _PosY, float _PosZ)
{
	// ** 3항 연산자
	// _Texture의 값이 nullptr이면 SetName()함수 실행
	// 아니라면 _Texture 값 대입
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;

	_Object->Speed = 0;

	// ** 좌표값
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** 회전값 (현재 사용 안함)
	_Object->TransInfo.Rotation = Vector3(0.0f, 0.0f, 0.0f);

	// ** 크기값
	_Object->TransInfo.Scale = Vector3((float)strlen(_Object->Info.Texture), 1.0f, 0.0f);

}

char* SetName()
{
	// 포인터 변수에는 바로 입력받을 수 없기 때문에 문자열을 입력 받을 임시 변수를 배열로 생성 
	char Buffer[128] = "";

	cout << "입력 : "; cin >> Buffer;

	// 포인터 변수를 선언하여 입력받은 문자열의 길이 + null 만큼의 크기를 할당
	//char* pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	// 입력받은 문자열의 내용 복사
	strcpy(pName, Buffer);

	// char* 반환
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
	// Position.x + Scale.x = 우측
	// Position.x = 좌측
	// Rect 충돌 시 우측값은 항상 크다
	if ((_ObjectA->TransInfo.Position.x + _ObjectA->TransInfo.Scale.x) > _ObjectB->TransInfo.Position.x &&
		(_ObjectB->TransInfo.Position.x + _ObjectB->TransInfo.Scale.x) > _ObjectA->TransInfo.Position.x &&
		_ObjectA->TransInfo.Position.y == _ObjectB->TransInfo.Position.y)
		return true;
	 return false;
}

Object* CreateBullet(const float _x, const float _y)
{
	// Bullet 생성 및 동적할당
	Object* _Object = new Object;

	// 안전을 위해 초기화 시 _x와 _y는 변경할 수 없는 상수로 받아옴
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
	// ** [상] 키를 입력받음.
	if (GetAsyncKeyState(VK_UP))
		_Object->TransInfo.Position.y -= 1;

	// ** [하] 키를 입력받음.
	if (GetAsyncKeyState(VK_DOWN))
		_Object->TransInfo.Position.y += 1;

	// ** [좌] 키를 입력받음.
	if (GetAsyncKeyState(VK_LEFT))
		_Object->TransInfo.Position.x -= 1;

	// ** [우] 키를 입력받음.
	if (GetAsyncKeyState(VK_RIGHT))
		_Object->TransInfo.Position.x += 1;
}
