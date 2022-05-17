// Framework v 0.2

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  // 입출력 헤더
#include <string>

using namespace std;	// iostream과 세트

//typedef struct tagInfo
//{
//	int iNumber;
//
//
//	tagInfo()	// 생성자, 구조체 안에서만 사용 가능
//	{
//		cout << "기본 생성자" << endl;	// 초기화 시 생성자 호출
//	};
//
//	tagInfo(int _iNumber)	
//	{
//		iNumber = _iNumber;
//		cout << "복사 생성자" << endl;	// 초기화 시 생성자 호출
//	};
//
//
//}INFO;


typedef struct Vector3
{
	int x = 0, y = 0, z = 0;

	Vector3() {};	//	기본 생성자 없이는

	Vector3(int _x, int _y)	// 복사 생성자를 만들 수 없다
		: x(_x), y(_y), z(0) { };

	Vector3(int _x, int _y, int _z)	
		: x(_x), y(_y), z(_z) { };


}Vector3;


struct Transform
{
	// 오브젝트가 존재하기 위해 필요한 최소한의 요소들
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

// 초기화 함수
void Initialize(Object* _Object, char* _Name, int _PosX = 0, int _PosY = 0, int _PosZ = 0);

// 이름 세팅 함수
char* SetName();

// 출력 함수
void Output(Object* _Object);



int main(void)
{
	// ** 출력
	//printf_s("문자 출력");
	//cout << "문자 출력";		// console out <<(시프트 연산자) "문자열"		
	
	//꺾쇠 방향으로  << 보내기, >> 받기


	// ** 줄바꿈
	//printf_s("\\n을 사용하면 \n줄바꿈");
	//cout << "endl 을 사용하면" << endl << "줄바꿈";


	/*
	// ** 입력
	int iNumber = 0;

	
	printf_s("입력: ");
	scanf("%d", &iNumber);

	printf_s("출력 : %d", iNumber);

	cout << "입력: ";
	cin >> iNumber;

	cout << "출력 : " << iNumber;
	*/

	// ** 동적할당 
	//INFO* pInfo = (INFO*)malloc(sizeof(INFO));		// malloc의 형태가 void* 이기 때문에 형변환
	//INFO* pInfo = new INFO;	// new는 동적할당, new 뒤의 INFO는 size 및 형태
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

	//Vector3 vPosition = Vector3(10, 20, 30);	// 매개변수의 개수나 형태에 따라 호출

	//cout << vPosition.x << ", " << vPosition.y << endl;

	// ** 플레이어 선언 및 동적할당
	Object* Player = new Object;

	// ** 플레이어 초기화
	Initialize(Player, nullptr, 10, 20, 30);

	Object* Enemy = new Object;
	Initialize(Enemy, (char*)"Enemy", 100, 200, 300);

	Output(Player);
	Output(Enemy);

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

void Initialize(Object* _Object, char* _Name, int _PosX, int _PosY, int _PosZ)
{
	// ** 3항 연산자
	// _Name의 값이 nullptr이면 SetName()함수 실행
	// 아니라면 _Name 값 대입
	_Object->Name = (_Name == nullptr) ? SetName() : _Name;

	_Object->Speed = 0;

	// ** 좌표값
	_Object->TramsInfo.Position = Vector3(_PosX, _PosY, _PosZ);

	// ** 회전값 (현재 사용 안함)
	_Object->TramsInfo.Rotation = Vector3(0, 0, 0);

	// ** 크기값
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
