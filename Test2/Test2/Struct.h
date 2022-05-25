#pragma once

struct Vector3
{
	float x = 0, y = 0, z = 0;

	Vector3() {};

	Vector3(float _x, float _y)
		: x(_x), y(_y), z(0) { };
};

struct Transform
{
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;
};

struct Player
{
	char* Name = { nullptr };
	char* Texture[4] = { (char*)"¥Ä", (char*)"¥Ð", (char*)"¡ì¥Ç¡í", (char*)"¡ý¡ý¡ý" };
	
	int Color[4] = { 11, 11, 11, 12 };

};

struct Enemy
{
	char* Texture[4] = { (char*)"¥´", (char*)"¢Ø¡Ô¢Ö", (char*)"¡Õ£Õ¡Õ", (char*)"¡«¡«¡«" };
	int Color[4] = { 4, 12, 12, 12 };
	ULONGLONG ETime;
};

struct Object
{
	Player Player;
	Enemy Enemy;
	Transform TransInfo;
};