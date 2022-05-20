#pragma once
// 구조체 관리

struct Vector3
{
	float x = 0, y = 0, z = 0;

	Vector3() {};	//	기본 생성자 없이는

	Vector3(float _x, float _y)	// 복사 생성자를 만들 수 없다
		: x(_x), y(_y), z(0) { };	// 사용하지 않는 변수도 초기화

	Vector3(float _x, float _y, float _z)	// 이름이 같아도 매개변수의 형태나 개수에 따라 맞는 함수 호출
		: x(_x), y(_y), z(_z) { };


};


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