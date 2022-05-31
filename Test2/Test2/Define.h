#pragma once

void Initialize(Object* _Object, float _PosX, float _PosY);

void PInitialize(Object* _Player, float _PosX = 0, float _PosY = 0, float _PosZ = 0);

void EInitialize(Object* _Enemy, float _PosX = 0, float _PosY = 0, float _PosZ = 0);

void ItemInit(Object* _Item, int _rand);

char* SetName();

void SetCursorPosition(const float _x, const float _y);

void SetTextColor(const int _Color);

BackGround* CreateBackGround(const int _rand);

void OnDrawBG(BackGround* _BG);

void OnDrawText(const char* _str, const float _x, const float _y, const int _Color = 15);

void OnDrawText(const int _Value, const float _x, const float _y, const int _Color = 15);

void HideCursor(const bool _Visible);

void LogoScene(Logo* _logo, ULONGLONG _t, ULONGLONG _load);

void MainScene();

void ScoreBoard();

Object* CreateEnemy(const float _x, const float _y, ULONGLONG _time);

void EnemyMove(Object* _Enemy, Vector3 _Direction, int _x);

Object* CreateAlly(const float _x, const float _y, const int _i);

float GetDistance(const Object* _ObjectA, const Object* _ObjectB);

Vector3 GetDirection(const Object* _ObjectA, const Object* _ObjectB);

Object* CreateBullet(const float _x, const float _y);

bool ECollision(const Object* _Object, const Object* _Enemy);

bool PCollision(const Object* _Object, const Object* _Player);

void UpdateInput(Object* _Object);

void ScoreP(const int _i);

Object* CreateItem(const int _rand);

void Warning(const int _x, const int _y);

void BossScene();




void Initialize(Object* _Object, float _PosX, float _PosY) 
{
	_Object->TransInfo.Position = Vector3(_PosX, _PosY);

	_Object->TransInfo.Rotation = Vector3(0.0f, 0.0f);

	_Object->TransInfo.Scale = Vector3(2.0f, 1.0f);
}

void PInitialize(Object* _Player, float _PosX , float _PosY, float _PosZ)
{
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

void ItemInit(Object* _Item, int _rand)
{
	if (_rand % 2 == 0)
	{
		_Item->Item.Option = 1;
		_Item->Item.Texture[0] = (char*)" x2 ";
		_Item->Item.Texture[1] = (char*)"∥∥";
	}
	if (_rand % 2 == 1)
	{
		_Item->Item.Option = 2;
		_Item->Item.Texture[0] = (char*)" +1 ";
		_Item->Item.Texture[1] = (char*)" HP ";
	}

	_Item->TransInfo.Position = Vector3((_rand % 30 * 2) + 20 , 1.0f);
	_Item->TransInfo.Rotation = Vector3(0.0f, 0.0f);
	_Item->TransInfo.Scale = Vector3((float)strlen(_Item->Item.Texture[0]), 2.0f);
}

void SetCursorPosition(const float _x, const float _y)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

char* SetName()
{
	char Buffer[128] = "";

	cout << "입력 : "; cin >> Buffer;

	char* pName = new char[strlen(Buffer) + 1];

	strcpy(pName, Buffer);

	return pName;
}

void SetTextColor(const int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

BackGround* CreateBackGround(const int _rand)
{
	BackGround* _BG = new BackGround;
	_BG->Texture = (char*)"*";

	_BG->TransInfo.Position.x = _rand % 120;
	_BG->TransInfo.Position.y = 1;
	_BG->Color = _rand % 9 + 5;

	return _BG;
}

void OnDrawBG(BackGround* _BG)
{
	OnDrawText(_BG->Texture,
		_BG->TransInfo.Position.x,
		_BG->TransInfo.Position.y,
		_BG->Color);
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
	else if (_Object->Item.Option == 1 || _Object->Item.Option == 2)
	{
		OnDrawText(_Object->Item.Texture[0],
			_Object->TransInfo.Position.x - 2,
			_Object->TransInfo.Position.y,
			_Object->Item.Color);
		OnDrawText(_Object->Item.Texture[1],
			_Object->TransInfo.Position.x - 2,
			_Object->TransInfo.Position.y - 1,
			_Object->Item.Color);
	}
	else if (_Object->Enemy.ETime != 0)
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

void LogoScene(Logo* _logo,ULONGLONG _t, ULONGLONG _load)
{
	int count = 0;
	for (int i = 0; i < 40; ++i)
	{
		OnDrawText(_logo->Texture[i], 0, 0 + i);
	}

	
	while (_t + 2500 > GetTickCount64())
	{
		if (_load + 50 < GetTickCount64())
		{
			_load = GetTickCount64();
			for (int i = 0; count < 40; ++i)
			{
				OnDrawText("▨", 20.0f + count * 2, 56, 10);
				count++;

				break;
			}
		}
	}
	
}

 

 
                                        

void MainScene()
{

}

//void ScoreBoard(int _arr[], char* _name[][4])
void ScoreBoard()
{
	system("cls");

	int Width = 60 - strlen("┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒") / 2;
	int Height = 7;
	OnDrawText((char*)".-. .-. .-. .-. .-. .-. .-. .-. .-. .-.", 40.0f, 2.0f, 14);
	OnDrawText((char*)"`-. |   | | |(  |-  |(  | | |-| |(  |  )", 40.0f, 3.0f, 14);
	OnDrawText((char*)"`-' `-' `-' ' ' `-' `-' `-' ` ' ' ' `-'", 40.0f, 4.0f, 14);
	
	OnDrawText((char*)"┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒", Width, Height, 15);
	OnDrawText((char*)"ㅣ                     .                                                                     ㅣ", Width, Height + 1, 15);
	OnDrawText((char*)"ㅣ                    '|                                                                     ㅣ", Width, Height + 2, 15);
	OnDrawText((char*)"ㅣ                    '-'                                                                    ㅣ", Width, Height + 3, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 4, 15);
	OnDrawText((char*)"ㅣ                    ,-.                                                                    ㅣ", Width, Height + 5, 15);
	OnDrawText((char*)"ㅣ                     /                                                                     ㅣ", Width, Height + 6, 15);
	OnDrawText((char*)"ㅣ                    '--                                                                    ㅣ", Width, Height + 7, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 8, 15);
	OnDrawText((char*)"ㅣ                    --.                                                                    ㅣ", Width, Height + 9, 15);
	OnDrawText((char*)"ㅣ                    --|                                                                    ㅣ", Width, Height + 10, 15);
	OnDrawText((char*)"ㅣ                    --'                                                                    ㅣ", Width, Height + 11, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 12, 15);
	OnDrawText((char*)"ㅣ                     ,.                                                                    ㅣ", Width, Height + 13, 15);
	OnDrawText((char*)"ㅣ                    '-|                                                                    ㅣ", Width, Height + 14, 15);
	OnDrawText((char*)"ㅣ                      '                                                                    ㅣ", Width, Height + 15, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 16, 15);
	OnDrawText((char*)"ㅣ                     .--                                                                    ㅣ", Width, Height + 17, 15);
	OnDrawText((char*)"ㅣ                     '-.                                                                    ㅣ", Width, Height + 18, 15);
	OnDrawText((char*)"ㅣ                     `-'                                                                    ㅣ", Width, Height + 19, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 20, 15);
	OnDrawText((char*)"ㅣ                      ,-                                                                   ㅣ", Width, Height + 21, 15);
	OnDrawText((char*)"ㅣ                     :-.                                                                   ㅣ", Width, Height + 22, 15);
	OnDrawText((char*)"ㅣ                     `-'                                                                   ㅣ", Width, Height + 23, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 24, 15);
	OnDrawText((char*)"ㅣ                     --,                                                                   ㅣ", Width, Height + 25, 15);
	OnDrawText((char*)"ㅣ                      /                                                                    ㅣ", Width, Height + 26, 15);
	OnDrawText((char*)"ㅣ                     '                                                                     ㅣ", Width, Height + 27, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 28, 15);
	OnDrawText((char*)"ㅣ                     ,-.                                                                   ㅣ", Width, Height + 29, 15);
	OnDrawText((char*)"ㅣ                     :-:                                                                   ㅣ", Width, Height + 30, 15);
	OnDrawText((char*)"ㅣ                     `-'                                                                   ㅣ", Width, Height + 31, 15);
	OnDrawText((char*)"┖ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┚", Width, Height + 32, 15);
	Sleep(10000);

	
                                      
             
             
             
                                      

}

Object* CreateEnemy(const float _x, const float _y, ULONGLONG _time)
{
	Object* _Enemy = new Object;

	PInitialize(_Enemy, _x, _y);

	_Enemy->Enemy.ETime = _time;

	return _Enemy;
}

void EnemyMove(Object* _Enemy, Vector3 _Direction , int _x)
{
	switch(_x)
	{
	case 1:
		if (_Enemy->TransInfo.Position.x > 4)
			_Enemy->TransInfo.Position.x--;
	case 2:
		if (_Enemy->TransInfo.Position.x < 116)
			_Enemy->TransInfo.Position.x++;
	case 3:
		if (_Enemy->TransInfo.Position.y < 56)
			_Enemy->TransInfo.Position.y++;
	case 4:
		if (_Enemy->TransInfo.Position.y > 40)
			_Enemy->TransInfo.Position.y--;
	case 5:
		if (_Enemy->TransInfo.Position.x > 4 &&
			_Enemy->TransInfo.Position.x < 116 &&
			_Enemy->TransInfo.Position.y < 56 &&
			_Enemy->TransInfo.Position.y > 40)
		{
			_Enemy->TransInfo.Position.x += _Direction.x;
			_Enemy->TransInfo.Position.y += _Direction.y;			
		}
			
	}
		
}

Object* CreateAlly(const float _x, const float _y, const int _i)
{
	Object* _Ally = new Object;

	PInitialize(_Ally, _x, _y);

	_Ally->Player.Name = (char*)"a";

	return _Ally;
}

float GetDistance(const Object* _ObjectA, const Object* _ObjectB)
{
	float x = _ObjectA->TransInfo.Position.x - _ObjectB->TransInfo.Position.x;
	float y = _ObjectA->TransInfo.Position.y - _ObjectB->TransInfo.Position.y;

	return sqrt((x * x) + (y * y));
}

Vector3 GetDirection(const Object* _ObjectA, const Object* _ObjectB)
{
	float x = _ObjectA->TransInfo.Position.x - _ObjectB->TransInfo.Position.x;
	float y = _ObjectA->TransInfo.Position.y - _ObjectB->TransInfo.Position.y;

	float Distance = sqrt((x * x) + (y * y));

	return Vector3(x / Distance, y / Distance);
}

Object* CreateBullet(const float _x, const float _y)
{
	Object* _Object = new Object;

	Initialize(_Object, _x, _y);

	return _Object;
}

bool ECollision(const Object* _Object, const Object* _Enemy)
{
	if (_Object->TransInfo.Position.y <= _Enemy->TransInfo.Position.y &&
		_Object->TransInfo.Position.y >= (_Enemy->TransInfo.Position.y - 2) &&
		_Object->TransInfo.Position.x >= (_Enemy->TransInfo.Position.x - 3) &&
		_Object->TransInfo.Position.x <= (_Enemy->TransInfo.Position.x + 3))
		return true;
	return false;
}

bool PCollision(const Object* _Object, const Object* _Player)
{
	if (_Object->TransInfo.Position.y >= _Player->TransInfo.Position.y &&
		_Object->TransInfo.Position.y <= (_Player->TransInfo.Position.y + 3) && 
		_Object->TransInfo.Position.x == _Player->TransInfo.Position.x)
		return true;
	return false;
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

void ScoreP(const int _i)
{
	OnDrawText((char*)"+", 12.0f, 1.0f, 14);
	OnDrawText(_i, 14.0f , 1.0f, 14);
}

Object* CreateItem(const int _rand)
{
	Object* _Item = new Object;

	ItemInit(_Item, _rand);

	return _Item;
}

// 고치기
void Warning(const int _x, const int _y)
{
	for (int i = 0; i + _y < 60; ++i)
	{
		switch (i % 9)
		{
		case 0:
			OnDrawText((char*)"/", _x, _y + i, 12);
			break;
		case 1:
			OnDrawText((char*)"W", _x, _y + i, 12);
			break;
		case 2:
			OnDrawText((char*)"A", _x, _y + i, 12);
			break;
		case 3:
			OnDrawText((char*)"R", _x, _y + i, 12);
			break;
		case 4:
			OnDrawText((char*)"N", _x, _y + i, 12);
			break;
		case 5:
			OnDrawText((char*)"I", _x, _y + i, 12);
			break;
		case 6:
			OnDrawText((char*)"N", _x, _y + i, 12);
			break;
		case 7:
			OnDrawText((char*)"G", _x, _y + i, 12);
			break;
		case 8:
			OnDrawText((char*)"!", _x, _y + i, 12);
			break;
		}
	}
}

void BossScene()
{
	float Width = 6.0f;
	float Height = 0.0f;
	OnDrawText((char*)"MMMMFVVVVFVVIMMMMMMMMMMNMNNMNNMMMFFNNNNNMVVVVV**VV*V*VV*IFFVVVVVVVFIMMMMMIFIMMMIFFFIIIIVVVVFVVVVVVV*****VMNN", Width, Height);
	OnDrawText((char*)"MMM::.:.::.:::::.:::..:****:::..:****:::**VVVVV*V**V:*F*VFV***VFF*::::*::*:::::*****:::**::*********:****MMM", Width, Height + 1);
	OnDrawText((char*)"MMM::*********::::::.:::***:::..:**:::*:VVVV**VV*.:VVFV**FV***VFII:..::**::::******:::::::**:***********VMMM", Width, Height + 2);
	OnDrawText((char*)" MMMVM*::**::*****::::::*****:..::***:**VFVV**VV**::VV**VIFV**VFII**:****::::*******:::*******:******NNVMNM ", Width, Height + 3);
	OnDrawText((char*)"  VV  NN************:******V**:::********VV**VVVV*******VMF**VVVIV********:::*VVV**************VVFFIIM  VV  ", Width, Height + 4);
	OnDrawText((char*)"        NMMMFVVVV***::******************VIVVVFVFVV******FMIVVVVVIM:.*V*******V*********VVVFIIIMMMNNN        ", Width, Height + 5);
	OnDrawText((char*)"          VV  NNNM*VVVVVVV**************VFFVVFFFVV******VIFVVIVFII**VV********VVVVFVVVVV:MNNNN  VV          ", Width, Height + 6);
	OnDrawText((char*)"                  VFNNMFIMIIVVVVVV**VVV**VFVVVVFFV*VVVFVVIFFVVVFMI*VVVVVVVFVV*VMIIMFIN M*N                  ", Width, Height + 7);
	OnDrawText((char*)"                  VV  NVFVVI*:MMMIIVVFFV*VMFVVVFFVVVVFVFVVFFVVVFMVVFFFVIMMMMM*VIVVFVIN  VV                  ", Width, Height + 8);
	OnDrawText((char*)"                      NVVVVFFM VV MFIFVVVFIVVFIII**VVVVVV**IIFVVFVFFVVMFMN VV NMV*FVVN                      ", Width, Height + 9);
	OnDrawText((char*)"                      NVVVVVIN    M*VVVFN   IFVVV***VVVV***VVFFN   NV*FVIN    MM*VFVVN                      ", Width, Height + 10);
	OnDrawText((char*)"                      NFVVVVIN    M*VVVFN   VVVVVV**V::V**VVVMVV   NVVIVVN    NMVVVFVN                      ", Width, Height + 11);
	OnDrawText((char*)"                       VVVVVV     M*VFVFN     MVVVV**::**VVVMM     NVVVVFN     VVVVVV                       ", Width, Height + 12);
	OnDrawText((char*)"                        VVVV       VVVVV       MFVVN****NVFNM       VVVVV       VVVV                        ", Width, Height + 13);
	OnDrawText((char*)"                                    VVV         MIVVV**VVVIM         VVV                                    ", Width, Height + 14);
	OnDrawText((char*)"                                                 NMVVVVVIMN                                                 ", Width, Height + 15);
	OnDrawText((char*)"                                                   MFVVIM                                                   ", Width, Height + 16);
	OnDrawText((char*)"                                                    NNNN                                                    ", Width, Height + 17);
}
