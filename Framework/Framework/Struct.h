#pragma once
// ����ü ����

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