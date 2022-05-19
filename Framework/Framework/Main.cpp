// Framework v 0.3

// 플레이어 몬스터 씬관리 투사체 충돌

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  // 입출력 헤더
#include <Windows.h>
#include <string>

using namespace std;	// iostream과 세트


typedef struct Vector3
{
	int x = 0, y = 0, z = 0;

	Vector3() {};	//	기본 생성자 없이는

	Vector3(int _x, int _y)	// 복사 생성자를 만들 수 없다
		: x(_x), y(_y), z(0) { };	// 사용하지 않는 변수도 초기화

	Vector3(int _x, int _y, int _z)	// 이름이 같아도 매개변수의 형태나 개수에 따라 맞는 함수 호출
		: x(_x), y(_y), z(_z) { };


}Vector3;


struct Transform
{
	// 오브젝트가 존재하기 위해 필요한 최소한의 요소들
	Vector3 Position;	// 좌표
	Vector3 Rotation;	// 회전률
	Vector3 Scale;		// 크기
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

// 초기화 함수 {디폴트 매개변수 : int _Value = 0, 디폴트는 함수 정의부에서 사용 불가하며 뒤에서부터 채워줘야 함(_X = 1, _Y, _Z = 3 안됨)}
void Initialize(Object* _Object, char* _Texture, int _PosX = 0, int _PosY = 0, int _PosZ = 0);

// 이름 세팅 함수
char* SetName();

// 커서의 위치를 변경
void SetCursorPosition(int _x, int _y);

// Text의 색을 변경
void SetTextColor(int _Color);

// 출력할 Text의 위치와 색상을 변경해준다 (Color default = 흰색)
void OnDrawText(char* _str, int _x, int _y, int _Color = 15);

// 출력할 숫자의 위치와 색상을 변경해준다
void OnDrawText(int _Value, int _x, int _y, int _Color = 15);

// 커서를 나타내거나(True) 숨기는(False) 함수
void HideCursor(bool _Visible);


int main(void)
{
	
	int Score = 0;

	HideCursor(false); // 커서를 숨김

	// 배경 초기화
	
	DrawTextInfo BackGround[30];


	for (int i = 0; i < 30; ++i)
	{
		// 랜덤값을 초기화 해줌, 큰 값이 나올 수 있도록 time값끼리 곱해줄 것이지만
		// for문이 빠르게 돌게되면 time의 증가값보다 빠를 수 있기 때문에
		// 랜덤값이라고 하더라도 연속으로 같은 값이 나올 수 있음
		// i의 값을 곱하고 더해줌으로써 중복값이 나오지 않도록 해줌
		srand((GetTickCount() + i * i)* GetTickCount());


		// 현재 어떻게 사용할지 정하지 않았지만, 추후 배경과 총알을 구분지어 플레이어가 배경과 닿았을때
		// 총알에 닿았을 때에만 충돌판정이 되도록 설정해줄 것임
		BackGround[i].Info.Option = 0;

		// 좌표를 랜덤으로 설정
		BackGround[i].TransInfo.Position.x = rand() % 100 + 10;
		BackGround[i].TransInfo.Position.y = rand() % 26 + 1;

		BackGround[i].Info.Texture = (char*)"*";

		BackGround[i].Info.Color = rand() % 8 + 1;

	}



	// ** 플레이어 선언 및 동적할당
	Object* Player = new Object;

	// ** 플레이어 초기화
	Initialize(Player, (char*)"옷/", 30, 10);

	Object* Enemy = new Object;
	Initialize(Enemy, (char*)"홋", 80, 10);

	// 현재 시간으로 초기화
	ULONGLONG Time = GetTickCount64();

	// 출력
	while (true)
	{
		// 초기화된 시간부터 +50만큼 증가하면
		// 프레임과 프레임 사이의 시간 간격을 0.5초로 세팅
		if (Time + 80 < GetTickCount64())
		{
			// 증가된 값만큼 다시 초기화
			Time = GetTickCount64();

			system("cls");

			// ** 배경 출력
			for (int i = 0; i < 30; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);

				// ** 배경으로 사용될 텍스처의 색상을 랜덤으로 설정.
				BackGround[i].Info.Color = rand() % 8 + 1;
			}

			// 상 키를 입력받음
			if (GetAsyncKeyState(VK_UP))
			{
				Player->TransInfo.Position.y -= 1;
			}

			// 하 키를 입력받음
			if (GetAsyncKeyState(VK_DOWN))
			{
				Player->TransInfo.Position.y += 1;
			}

			// 좌 키를 입력받음
			if (GetAsyncKeyState(VK_LEFT))
			{
				Player->TransInfo.Position.x -= 1;
			}

			// 우 키를 입력받음
			if (GetAsyncKeyState(VK_RIGHT))
			{
				Player->TransInfo.Position.x += 1;
			}
			
			// 스페이스 키를 입력받음
			if (GetAsyncKeyState(VK_SPACE))
				Player->Info.Texture = (char*)"옷ㅡ";
			else
				Player->Info.Texture = (char*)"옷/";

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

void Initialize(Object* _Object, char* _Texture, int _PosX, int _PosY, int _PosZ)
{
	// ** 3항 연산자
	// _Texture의 값이 nullptr이면 SetName()함수 실행
	// 아니라면 _Texture 값 대입
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;

	_Object->Speed = 0;

	// ** 좌표값
	_Object->TransInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** 회전값 (현재 사용 안함)
	_Object->TransInfo.Rotation = Vector3(0, 0, 0);

	// ** 크기값
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
