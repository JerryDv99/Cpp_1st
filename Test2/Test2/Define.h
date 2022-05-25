#pragma once

void PInitialize(Object* _Player, float _PosX = 0, float _PosY = 0, float _PosZ = 0);

void EInitialize(Object* _Enemy, float _PosX = 0, float _PosY = 0, float _PosZ = 0);

char* SetName();

void SetCursorPosition(const float _x, const float _y);

void SetTextColor(const int _Color);

void OnDrawText(const char* _str, const float _x, const float _y, const int _Color = 15);

void OnDrawText(const int _Value, const float _x, const float _y, const int _Color = 15);

void HideCursor(const bool _Visible);

void UpdateInput(Object* _Object);





void PInitialize(Object* _Player, float _PosX , float _PosY, float _PosZ)
{
	_Player->Player.Name = { nullptr };

	_Player->TransInfo.Position = Vector3(_PosX, _PosY);

	_Player->TransInfo.Rotation = Vector3(0.0f, 0.0f);

	_Player->TransInfo.Scale = Vector3((float)strlen(_Player->Player.Texture[3]), 4.0f);
}

void EInitialize(Object* _Enemy, float _PosX , float _PosY, float _PosZ)
{
	_Enemy->TransInfo.Position = Vector3(_PosX, _PosY);
	
	_Enemy->TransInfo.Rotation = Vector3(0.0f, 0.0f);

	_Enemy->TransInfo.Scale = Vector3((float)strlen(_Enemy->Enemy.Texture[0]), 4.0f);

	_Enemy->Enemy.ETime = 0;
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

void OnDrawObj(Object* _Object, const float _x, const float _y)
{
	
	if (_Object->Player.Name != nullptr)
	{
		OnDrawText(_Object->Player.Texture[0], 
			_Object->TransInfo.Position.x,
			_Object->TransInfo.Position.y,
			_Object->Player.Color[0]);
		OnDrawText(_Object->Player.Texture[1],
			_Object->TransInfo.Position.x,
			_Object->TransInfo.Position.y + 1,
			_Object->Player.Color[1]);
		OnDrawText(_Object->Player.Texture[2],
			_Object->TransInfo.Position.x - 2,
			_Object->TransInfo.Position.y + 2,
			_Object->Player.Color[2]);
		OnDrawText(_Object->Player.Texture[3],
			_Object->TransInfo.Position.x - 2,
			_Object->TransInfo.Position.y + 3,
			_Object->Player.Color[3]);

	}
	else
	{
		OnDrawText(_Object->Enemy.Texture[0],
			_Object->TransInfo.Position.x,
			_Object->TransInfo.Position.y,
			_Object->Enemy.Color[0]);
		OnDrawText(_Object->Enemy.Texture[1],
			_Object->TransInfo.Position.x - 2,
			_Object->TransInfo.Position.y - 1,
			_Object->Enemy.Color[1]);
		OnDrawText(_Object->Enemy.Texture[2],
			_Object->TransInfo.Position.x - 2,
			_Object->TransInfo.Position.y - 2,
			_Object->Enemy.Color[2]);
		OnDrawText(_Object->Enemy.Texture[3],
			_Object->TransInfo.Position.x - 2,
			_Object->TransInfo.Position.y - 3,
			_Object->Enemy.Color[3]);

	}
}

void HideCursor(const bool _Visible)
{
	CONSOLE_CURSOR_INFO CursorInfo;

	CursorInfo.bVisible = _Visible;
	CursorInfo.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}

void UpdateInput(Object* _Object)
{
	if (_Object->TransInfo.Position.y >= 20)
	{
		if (GetAsyncKeyState(VK_UP))
			_Object->TransInfo.Position.y -= 1;
	}
	
	if (_Object->TransInfo.Position.y < 56)
	{
		if (GetAsyncKeyState(VK_DOWN))
			_Object->TransInfo.Position.y += 1;
	}
		  
	if (_Object->TransInfo.Position.x > 2)
	{
		if (GetAsyncKeyState(VK_LEFT))
			_Object->TransInfo.Position.x -= 2;
	}

	if (_Object->TransInfo.Position.x < 116)
	{
		if (GetAsyncKeyState(VK_RIGHT))
			_Object->TransInfo.Position.x += 2;
	}
	
}