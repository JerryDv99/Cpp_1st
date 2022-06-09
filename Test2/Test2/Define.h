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

void LogoScene(sLogo* _logo, ULONGLONG _t, ULONGLONG _load);

void MainScene(Object* _icon, int _arr[], char _name[][4]);

void ScoreBoard(int _arr[], char _name[][4]);

void Tutorial(Object* _Player, ULONGLONG _time, Object* _E1, Object* _E2, Object* _E3);

Object* CreateEnemy(const float _x, const float _y, ULONGLONG _time);

void EnemyMove(Object* _Enemy, Vector3 _Direction, int _x);

Object* CreateAlly(const float _x, const float _y, const int _i);

float GetDistance(const Object* _ObjectA, const Object* _ObjectB);

Vector3 GetDirection(const Object* _ObjectA, const Object* _ObjectB);

Object* CreateBullet(const float _x, const float _y);

bool ECollision(const Object* _Object, const Object* _Enemy);

bool PCollision(const Object* _Object, const Object* _Player);

void UpdateInput(Object* _Object);

void UpdateInput1(Object* _Object);

void ScoreP(const int _i);

Object* CreateItem(const int _rand);

void Warning(const int _x, const int _y);

void Warning2(const int _y);

void BossScene();

void BossTuto();

Vector3 Direction;

ULONGLONG Time = GetTickCount64();
ULONGLONG Logo = GetTickCount64();
ULONGLONG Loading = GetTickCount64();
ULONGLONG BG = GetTickCount64();
ULONGLONG GameTime = GetTickCount64();
ULONGLONG EnemyTime1 = GetTickCount64();
ULONGLONG Cooling1 = GetTickCount64();
ULONGLONG ERR1 = GetTickCount64();
ULONGLONG Loaded1 = GetTickCount64();
ULONGLONG DropItem1 = GetTickCount64();
ULONGLONG BuffTime1 = GetTickCount64();
ULONGLONG AllyB = GetTickCount64();
ULONGLONG StoryTime = GetTickCount64();

ULONGLONG Tuto1 = GetTickCount64();
ULONGLONG Tuto2 = GetTickCount64();
ULONGLONG Tuto3 = GetTickCount64();
ULONGLONG Tuto4 = GetTickCount64();
ULONGLONG Tuto5 = GetTickCount64();
ULONGLONG Tuto6 = GetTickCount64();

ULONGLONG R1Time = GetTickCount64();



Object* Bullet[256] = { nullptr };
Object* EBullet[128] = { nullptr };
Object* Missile[8] = { nullptr };
Object* EMissile[8] = { nullptr };
Object* Item[2] = { nullptr };



bool first = true;
bool Story1 = false;
bool Story2 = false;
bool Story3 = false;
bool Story4 = false;
bool loop = true;
bool Story = false;
bool Check = false;
bool OHeat = false;
bool Load = false;
bool BBuff = false;
bool MBuff = false;
bool Exit = false;

bool UI = true;
bool E1V = false;
bool E2V = false;
bool E3V = false;

bool R1 = false;
bool RCheck = false;
bool LCheck = false;
bool Main = true;
bool BR = false;

bool tuto1 = false;
bool tuto2 = false;
bool tuto3 = false;
bool tuto4 = false;
bool tuto5 = false;
bool tuto6 = false;
bool tuto7 = false;

int Score = 0;
int Kill = 0;
int MKill = 0;
int ECount = 0;
int Life = 2;	// 재도전 기회
int T;

float Heat = 0.0f;


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
	if (_rand % 3 == 0)
	{
		_Item->Item.Option = 1;
		_Item->Item.Texture[0] = (char*)" x2 ";
		_Item->Item.Texture[1] = (char*)"∥∥";
	}
	if (_rand % 3 == 1)
	{
		_Item->Item.Option = 2;
		_Item->Item.Texture[0] = (char*)" +1 ";
		_Item->Item.Texture[1] = (char*)" HP ";
	}
	if (_rand % 3 == 2)
	{
		_Item->Item.Option = 3;
		_Item->Item.Texture[0] = (char*)" x3 ";
		_Item->Item.Texture[1] = (char*)"ΛΛ";
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

	cout << " : "; cin >> Buffer;

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
	else if (_Object->Item.Option == 1 || _Object->Item.Option == 2 || _Object->Item.Option == 3)
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

void LogoScene(sLogo* _logo, ULONGLONG _t, ULONGLONG _load)
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

void MainScene(Object* _icon, int _arr[], char _name[][4])
{
	system("cls");

	int Width = 12;
	int Height = 7;

	OnDrawText((char*)"                                             *N*                                                ", Width, Height ,9);
	OnDrawText((char*)"                                             MNN*                                               ", Width, Height + 1,9);
	OnDrawText((char*)"                                            *NNNF                                               ", Width, Height + 2,9);
	OnDrawText((char*)"                                            VNNNN*                                              ", Width, Height + 3,9);
	OnDrawText((char*)"                                            MNNNNV                                              ", Width, Height + 4,9);
	OnDrawText((char*)"                                           *NFVFNF                                              ", Width, Height + 5,9);
	OnDrawText((char*)"                                           *N   VM                                              ", Width, Height + 6,9);
	OnDrawText((char*)"                                           *N***VN                                              ", Width, Height + 7,9);
	OnDrawText((char*)"                                           *N   *N                                              ", Width, Height + 8,9);
	OnDrawText((char*)"                                           *N   VN                                              ", Width, Height + 9,9);
	OnDrawText((char*)"                                           *N***VN                                              ", Width, Height + 10,9);
	OnDrawText((char*)"                                           *N   VN                                              ", Width, Height + 11,9);
	OnDrawText((char*)"                                        IMVVN   *NVMM*                                          ", Width, Height + 12,9);
	OnDrawText((char*)"                                       *NNNNN   *$NNNV                                          ", Width, Height + 13,9);
	OnDrawText((char*)"                                     *INNNNNN***INNNNNN*                                        ", Width, Height + 14,9);
	OnDrawText((char*)"                                    VNNNNNNNNNNNNNNNNNNNV                                       ", Width, Height + 15,9);
	OnDrawText((char*)"                                   VNNNNNNNNNNNNNNNNNNNNNM*                                     ", Width, Height + 16,9);
	OnDrawText((char*)"                                  *INNNNNNNNNNNNNNNNNNNNNMV                                     ", Width, Height + 17,9);
	OnDrawText((char*)"                                    VVVVVVVVINNNMFVVVVVVV*                                      ", Width, Height + 18,9);
	OnDrawText((char*)"FNMMMMMMMMMMMMMMMMMMMM                        VV                        MMMMMMMMMMMMMMMMMMMMMMM*", Width, Height + 19,9);
	OnDrawText((char*)" *VVVVVVVVVVVVVVVVVVVV                                                   VVVVVVVVVVVVVVVVVVVVV* ", Width, Height + 20,12);
	OnDrawText((char*)"  *INNNNNNNNNNNNNNNNNM                                                   VNNNNNNNNNNNNNNNNNMV   ", Width, Height + 21,12);
	OnDrawText((char*)"    *VFFFFFFFFFFFFFFFV                                                   VFFFFFFFFFFFFFFFFV     ", Width, Height + 22,12);
	OnDrawText((char*)"     *FMMIMMIIIIIMMMMI                                                   VMIIIMMMMMIIIIIIV      ", Width, Height + 23,12);
	OnDrawText((char*)"       *FFFFFFFFFFFFFF                                                   VFFFFFFFFFFFFIV        ", Width, Height + 24,12);
	OnDrawText((char*)"        *VFFFFVVVVFVFV                                                   VFFFFFFFFVFFV*         ", Width, Height + 25,12);
	OnDrawText((char*)"          VM$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$N*M*F$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$I*          ", Width, Height + 26,9);
	OnDrawText((char*)"            ****************VVVVVVVVVVVV*VVVVMNI*VV***VVVVVVVVVVVV******************            ", Width, Height + 27,9);
	OnDrawText((char*)"                          *MNNNNNNNNNINNFVVFNNNNNMVVFNNIMNNNNNNNNM*                             ", Width, Height + 28,9);
	OnDrawText((char*)"                          NNNNNNNNNF VNNNNM*IMINN*MNNNNV *MNNNNNNNN*                            ", Width, Height + 29,9);
	OnDrawText((char*)"                         FNNNNNNNI* VNNNNN**V*VVVVVNNNNNV  INNNNNNNN*                           ", Width, Height + 30,9);
	OnDrawText((char*)"                        FNNNNNNM*  VNNNNNF *FNNNMV*INNNNNM* *MNNNNNNN                           ", Width, Height + 31,9);
	OnDrawText((char*)"                       VNNNNNNV  VNNNNNNNMNNNNNNNNNMNNNNNNNF  *INNNNNI                          ", Width, Height + 32,9);
	OnDrawText((char*)"                       VNNNNF* *MNNNNNNNNNNNNNNNNNNNNNNNNNNNM*  VNNNNV                          ", Width, Height + 33,9);
	OnDrawText((char*)"                        VNI*  *NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNI* *FNN                           ", Width, Height + 34,9);
	OnDrawText((char*)"                         V  *FNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN*  **                           ", Width, Height + 35,9);
	OnDrawText((char*)"                           FNNNNNNNNNI*VMVVVNNNNNMVVMFVFNNNNNNNNNI                              ", Width, Height + 36,9);
	OnDrawText((char*)"                           MNNNNNNMIV*  V    V$F    V   VIMNNNNNNM*                             ", Width, Height + 37,9);
	OnDrawText((char*)"                            *VV**       *    *V*    *       ***VV                               ", Width, Height + 38,9);

	OnDrawText((char*)"MMMMMN  VNNMF  VMMNNIV  ", Width + 22, Height + 19, 9);
	OnDrawText((char*)"VINNV  MNV VN$ VNM  INF ", Width + 22, Height + 20, 9);
	OnDrawText((char*)" V$N   N$  *N$ FNI  FNI ", Width + 22, Height + 21, 9);
	OnDrawText((char*)" V$N   N$  *N$ VNNMMNI* ", Width + 22, Height + 22, 9);
	OnDrawText((char*)" V$N   N$  *N$ VNM      ", Width + 22, Height + 23, 9);
	OnDrawText((char*)" V$N   FNVVFNM VNI      ", Width + 22, Height + 24, 9);
	OnDrawText((char*)" VVV     VVV   VFV      ", Width + 22, Height + 25, 9);
	OnDrawText((char*)"  VFNNMV  MNV  MNN NMV  NM", Width + 48, Height + 19, 12);
	OnDrawText((char*)" V$N  F$M N$V  N$N $NN  $N ", Width + 48, Height + 20, 12);
	OnDrawText((char*)" V$N      N$V  N$M NNNNV$$ ", Width + 48, Height + 21, 12);
	OnDrawText((char*)" V$N VMMF N$V  N$V $MVNMNN ", Width + 48, Height + 22, 12);
	OnDrawText((char*)" V$N  FNM NNV  N$V NM VNNN ", Width + 48, Height + 23, 12);
	OnDrawText((char*)"  MNVVMNV FNMVFNMN $M  NNN ", Width + 48, Height + 24, 12);
	OnDrawText((char*)"   VFFV     VVVV   FV  VVV ", Width + 48, Height + 25, 12);
		
	OnDrawText((char*)"1 . START", 26, 52);
	OnDrawText((char*)"2 . RANK", 56, 52);
	OnDrawText((char*)"3 . EXIT", 86, 52);

	if (_icon->TransInfo.Position.x == 20 || _icon->TransInfo.Position.x == 50)
	{
		if (!RCheck && GetAsyncKeyState(VK_RIGHT) & 0x0001)
		{
			RCheck = true;
		}

		if (RCheck && !(GetAsyncKeyState(VK_RIGHT) & 0x8000))
		{
			_icon->TransInfo.Position.x += 30;
			RCheck = false;
		}			
	}
	if (_icon->TransInfo.Position.x == 50 || _icon->TransInfo.Position.x == 80)
	{
		if (!LCheck && GetAsyncKeyState(VK_LEFT) & 0x0001)
		{
			LCheck = true;
		}		
		if (LCheck && !(GetAsyncKeyState(VK_LEFT) & 0x8000))
		{
			_icon->TransInfo.Position.x -= 30;
			LCheck = false;
		}	
		
	}

	if (_icon->TransInfo.Position.x == 20)
		OnDrawText((char*)"1 . START", 26, 52, 10);
	if (_icon->TransInfo.Position.x == 50)
		OnDrawText((char*)"2 . RANK", 56, 52, 10);
	if (_icon->TransInfo.Position.x == 80)
		OnDrawText((char*)"3 . EXIT", 86, 52, 10);

	OnDrawText(_icon->Icon.Texture, _icon->TransInfo.Position.x, _icon->TransInfo.Position.y, 11);

	if (GetAsyncKeyState(VK_RETURN))
	{
		if (_icon->TransInfo.Position.x == 20)
			Main = false;
		if (_icon->TransInfo.Position.x == 50)
			ScoreBoard(_arr, _name);
		if (_icon->TransInfo.Position.x == 80)
			exit(NULL);

	}

}

void ScoreBoard(int _arr[], char _name[][4])
{
	system("cls");
	HideCursor(false);

	int Width = 60 - strlen("┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒") / 2;
	int Height = 16;
	OnDrawText((char*)".-. .-. .-. .-. .-. .-. .-. .-. .-. .-.", 40.0f, 5.0f, 14);
	OnDrawText((char*)"`-. |   | | |(  |-  |(  | | |-| |(  |  )", 40.0f, 6.0f, 14);
	OnDrawText((char*)"`-' `-' `-' ' ' `-' `-' `-' ` ' ' ' `-'", 40.0f, 7.0f, 14);

	OnDrawText((char*)"┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒", Width, Height, 15);
	OnDrawText((char*)"ㅣ                            RANK  :           1st                                          ㅣ", Width, Height + 1, 15);
	OnDrawText((char*)"ㅣ                            SCORE :                                                        ㅣ", Width, Height + 2, 15);
	OnDrawText((char*)"ㅣ                            NAME  :                                                        ㅣ", Width, Height + 3, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 4, 15);
	OnDrawText((char*)"ㅣ                            RANK  :           2nd                                          ㅣ", Width, Height + 5, 15);
	OnDrawText((char*)"ㅣ                            SCORE :                                                        ㅣ", Width, Height + 6, 15);
	OnDrawText((char*)"ㅣ                            NAME  :                                                        ㅣ", Width, Height + 7, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 8, 15);
	OnDrawText((char*)"ㅣ                            RANK  :           3rd                                          ㅣ", Width, Height + 9, 15);
	OnDrawText((char*)"ㅣ                            SCORE :                                                        ㅣ", Width, Height + 10, 15);
	OnDrawText((char*)"ㅣ                            NAME  :                                                        ㅣ", Width, Height + 11, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 12, 15);
	OnDrawText((char*)"ㅣ                            RANK  :           4th                                          ㅣ", Width, Height + 13, 15);
	OnDrawText((char*)"ㅣ                            SCORE :                                                        ㅣ", Width, Height + 14, 15);
	OnDrawText((char*)"ㅣ                            NAME  :                                                        ㅣ", Width, Height + 15, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 16, 15);
	OnDrawText((char*)"ㅣ                            RANK  :           5th                                          ㅣ", Width, Height + 17, 15);
	OnDrawText((char*)"ㅣ                            SCORE :                                                        ㅣ", Width, Height + 18, 15);
	OnDrawText((char*)"ㅣ                            NAME  :                                                        ㅣ", Width, Height + 19, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 20, 15);
	OnDrawText((char*)"ㅣ                            RANK  :           6th                                          ㅣ", Width, Height + 21, 15);
	OnDrawText((char*)"ㅣ                            SCORE :                                                        ㅣ", Width, Height + 22, 15);
	OnDrawText((char*)"ㅣ                            NAME  :                                                        ㅣ", Width, Height + 23, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 24, 15);
	OnDrawText((char*)"ㅣ                            RANK  :           7th                                          ㅣ", Width, Height + 25, 15);
	OnDrawText((char*)"ㅣ                            SCORE :                                                        ㅣ", Width, Height + 26, 15);
	OnDrawText((char*)"ㅣ                            NAME  :                                                        ㅣ", Width, Height + 27, 15);
	OnDrawText((char*)"ㅣ                   ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ                    ㅣ", Width, Height + 28, 15);
	OnDrawText((char*)"ㅣ                            RANK  :           8th                                          ㅣ", Width, Height + 29, 15);
	OnDrawText((char*)"ㅣ                            SCORE :                                                        ㅣ", Width, Height + 30, 15);
	OnDrawText((char*)"ㅣ                            NAME  :                                                        ㅣ", Width, Height + 31, 15);
	OnDrawText((char*)"┖ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┚", Width, Height + 32, 15);

	OnDrawText((char*)" . ", Width + 22, Height + 1, 14);
	OnDrawText((char*)"'| ", Width + 22, Height + 2, 14);
	OnDrawText((char*)"'-'", Width + 22, Height + 3, 14);
	OnDrawText((char*)",-.", Width + 22, Height + 5, 8);
	OnDrawText((char*)" / ", Width + 22, Height + 6, 8);
	OnDrawText((char*)"'--", Width + 22, Height + 7, 8);
	OnDrawText((char*)"--.", Width + 22, Height + 9, 6);
	OnDrawText((char*)"--|", Width + 22, Height + 10, 6);
	OnDrawText((char*)"--'", Width + 22, Height + 11, 6);
	OnDrawText((char*)" ,.", Width + 22, Height + 13, 11);
	OnDrawText((char*)"'-|", Width + 22, Height + 14, 11);
	OnDrawText((char*)"  '", Width + 22, Height + 15, 11);
	OnDrawText((char*)".--", Width + 22, Height + 17, 11);
	OnDrawText((char*)"'-.", Width + 22, Height + 18, 11);
	OnDrawText((char*)"`-'", Width + 22, Height + 19, 11);
	OnDrawText((char*)" ,-", Width + 22, Height + 21, 11);
	OnDrawText((char*)":-.", Width + 22, Height + 22, 11);
	OnDrawText((char*)"`-'", Width + 22, Height + 23, 11);
	OnDrawText((char*)"--,", Width + 22, Height + 25, 11);
	OnDrawText((char*)" / ", Width + 22, Height + 26, 11);
	OnDrawText((char*)"'  ", Width + 22, Height + 27, 11);
	OnDrawText((char*)",-.", Width + 22, Height + 29, 11);
	OnDrawText((char*)":-:", Width + 22, Height + 30, 11);
	OnDrawText((char*)"`-'", Width + 22, Height + 31, 11);

	OnDrawText((char*)_name[0], 60, Height + 2, 14);
	OnDrawText(_arr[0], 60, Height + 3, 14);
	OnDrawText((char*)_name[1], 60, Height + 6, 14);
	OnDrawText(_arr[1], 60, Height + 7, 14);
	OnDrawText((char*)_name[2], 60, Height + 10, 14);
	OnDrawText(_arr[2], 60, Height + 11, 14);
	OnDrawText((char*)_name[3], 60, Height + 14, 14);
	OnDrawText(_arr[3], 60, Height + 15, 14);
	OnDrawText((char*)_name[4], 60, Height + 18, 14);
	OnDrawText(_arr[4], 60, Height + 19, 14);
	OnDrawText((char*)_name[5], 60, Height + 22, 14);
	OnDrawText(_arr[5], 60, Height + 23, 14);
	OnDrawText((char*)_name[6], 60, Height + 26, 14);
	OnDrawText(_arr[6], 60, Height + 27, 14);
	OnDrawText((char*)_name[7], 60, Height + 30, 14);
	OnDrawText(_arr[7], 60, Height + 31, 14);

	OnDrawText("Exit [X]", 56, 56, 10);
	
	while (true)
	{
		if (GetAsyncKeyState(0x58))
		{
			
			break;
		}
	}   
	HideCursor(true);
}

void Tutorial(Object* _Player, ULONGLONG _time, Object* _E1, Object* _E2, Object* _E3)
{
	int Height = 50;
	
	if (_time + 50 < GetTickCount64())
	{
		_time = GetTickCount64();
		system("cls");

		if (UI)
		{
			OnDrawText((char*)"┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒", 2, Height);
			OnDrawText((char*)"ㅣ                                                                                                                 ㅣ", 2, Height + 1);
			OnDrawText((char*)"ㅣ                                                                                                                 ㅣ", 2, Height + 2);
			OnDrawText((char*)"ㅣ                                                                                                                 ㅣ", 2, Height + 3);
			OnDrawText((char*)"ㅣ                                                                                                                 ㅣ", 2, Height + 4);
			OnDrawText((char*)"ㅣ                                                                                                                 ㅣ", 2, Height + 5);
			OnDrawText((char*)"ㅣ                                                                                                                 ㅣ", 2, Height + 6);
			OnDrawText((char*)"ㅣ                                                                                                                 ㅣ", 2, Height + 7);
			OnDrawText((char*)"ㅣ                                                                                                                 ㅣ", 2, Height + 8);
			OnDrawText((char*)"┖ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┚", 2, Height + 9);
		}
		
		if(tuto1)
		{
			OnDrawText((char*)"안녕하신가 신참, 나는 이 함대의 지휘관 로저스 제독일세. 자네 이름은 뭔가?", 60 - strlen("안녕하신가 신참, 나는 이 함대의 지휘관 로저스 제독일세. 자네 이름은 뭔가?") / 2, Height + 3);
			OnDrawText((char*)"이름 ", 52, Height + 6);
			_Player->Player.Name = SetName();	
			Tuto1 = GetTickCount64();
			tuto1 = false;
		}
		
		if (!tuto1 && tuto2)
		{
			if (Tuto1 + 3000 > GetTickCount64())
			{
				if (Tuto1 + 1000 > GetTickCount64())
				{
					OnDrawText((char*)"", 60 - strlen("") / 2, Height + 3);
					OnDrawText((char*)"┏ㅡㅡㅡㅡㅡ┑", _Player->TransInfo.Position.x - 5, _Player->TransInfo.Position.y - 1, 12);
					OnDrawText((char*)"ㅣ         ㅣ", _Player->TransInfo.Position.x - 5, _Player->TransInfo.Position.y, 12);
					OnDrawText((char*)"ㅣ         ㅣ", _Player->TransInfo.Position.x - 5, _Player->TransInfo.Position.y + 1, 12);
					OnDrawText((char*)"ㅣ         ㅣ", _Player->TransInfo.Position.x - 5, _Player->TransInfo.Position.y + 2, 12);
					OnDrawText((char*)"ㅣ         ㅣ", _Player->TransInfo.Position.x - 5, _Player->TransInfo.Position.y + 3, 12);
					OnDrawText((char*)"┖ㅡㅡㅡㅡㅡ┚", _Player->TransInfo.Position.x - 5, _Player->TransInfo.Position.y + 4, 12);
				}
				OnDrawText((char*)"빨갛게 표시된 기체가 자네일세", 60 - strlen("빨갛게 표시된 기체가 자네일세") / 2, Height + 3);
				OnDrawText((char*)"방향키로 이동할 수 있지", 60 - strlen("방향키로 이동할 수 있지") / 2, Height + 6);		
			}
			if (Tuto1 + 3000 < GetTickCount64())
			{
				Story = false;
				Tuto2 = GetTickCount64();
				E1V = true;
				tuto2 = false;
			}
			
		}

		if (!tuto2 && tuto3)
		{
			if (Tuto2 + 3000 > GetTickCount64())
			{
				if (Tuto2 + 1000 > GetTickCount64())
				{
					OnDrawText((char*)"", 60 - strlen("") / 2, Height + 3);
					OnDrawText((char*)"┏ㅡㅡㅡㅡㅡㅡ┑", _E1->TransInfo.Position.x - 6, _E1->TransInfo.Position.y - 4, 12);
					OnDrawText((char*)"ㅣ           ㅣ",_E1->TransInfo.Position.x - 6, _E1->TransInfo.Position.y - 3, 12);
					OnDrawText((char*)"ㅣ           ㅣ",_E1->TransInfo.Position.x - 6, _E1->TransInfo.Position.y - 2, 12);
					OnDrawText((char*)"ㅣ           ㅣ",_E1->TransInfo.Position.x - 6, _E1->TransInfo.Position.y - 1, 12);
					OnDrawText((char*)"ㅣ           ㅣ",_E1->TransInfo.Position.x - 6, _E1->TransInfo.Position.y, 12);
					OnDrawText((char*)"┖ㅡㅡㅡㅡㅡㅡ┚", _E1->TransInfo.Position.x - 6, _E1->TransInfo.Position.y + 1, 12);
				}
				OnDrawText((char*)"모의 적기를 추가했네", 60 - strlen("모의 적기를 추가했네") / 2, Height + 3);
				OnDrawText((char*)"스페이스 바를 눌러 일반 무장을 발사해보게", 60 - strlen("스페이스 바를 눌러 일반 무장을 발사해보게") / 2, Height + 6);				
			}
			if (Tuto2 + 1000 < GetTickCount64())
			{
				Tuto3 = GetTickCount64();
				tuto3 = false;
			}
		}

		if (!tuto3 && tuto4 && !E1V)
		{
			if (Tuto3 + 6000 > GetTickCount64())
			{
				OnDrawText((char*)"잘했네, 하지만 신참들 대부분이 허공에 총질을 하지", 60 - strlen("잘했네, 하지만 신참들 대부분이 허공에 총질을 하지") / 2, Height + 2);
				OnDrawText((char*)"일반 무장은 발사 중일때 계속 뜨거워지고 과열되면 3초 동안 냉각에 들어가 발사가 불가능하다", 60 - strlen("일반 무장은 발사 중일때 계속 뜨거워지고 과열되면 5초 동안 냉각에 들어가 발사가 불가능하다") / 2, Height + 4, 12);
				OnDrawText((char*)"열 수치는 우측 상단에서 확인할 수 있고 발사 중이 아닐땐 냉각장치가 작동되어 열 수치가 점점 떨어지니 참고하도록", 60 - strlen("열 수치는 우측 상단에서 확인할 수 있고 발사 중이 아닐땐 냉각장치가 작동되어 열 수치가 점점 떨어지니 참고하도록") / 2, Height + 6);
			}
			if (Tuto3 + 6000 < GetTickCount64())
			{
				Tuto4 = GetTickCount64();
				E2V = true;
				E3V = true;
				tuto4 = false;				
			}
		}
		
		if (!tuto4 && tuto5)
		{			
			if (Tuto4 + 7000 > GetTickCount64())
			{
				OnDrawText((char*)"적들도 당연히 무장이 있고 공격을 해온다네, 그에 맞설 미사일 사용법에 대해 알려주지", 60 - strlen("적들도 당연히 무장이 있고 공격을 해온다네, 그에 맞설 다음은 미사일 사용법에 대해 알려주지") / 2, Height + 1);
				OnDrawText((char*)"미사일 장전엔 5초가 소요되며 장전시간 또한 우측 상단에서 확인이 가능하지", 60 - strlen("미사일 장전엔 5초가 소요되며 장전시간 또한 우측 상단에서 확인이 가능하지") / 2, Height + 3);
				OnDrawText((char*)"[ x ] 키를 눌러 미사일을 발사하면, 적 투사체를 파괴하며 나아가 경로 상의 적을 최대 3기까지 파괴 가능하다네", 60 - strlen("[ x ] 키를 눌러 미사일을 발사하면, 적 투사체를 파괴하며 나아가 경로 상의 적을 최대 3기까지 파괴 가능하다네") / 2, Height + 5);
				OnDrawText((char*)"미사일로 적을 처치하면 보너스 점수가 크니 적재적소에 사용하도록", 60 - strlen("미사일로 적을 처치하면 보너스 점수가 크니 적재적소에 사용하도록") / 2, Height + 7);
			}
			if (!tuto4 && !E2V && !E3V)
			{
				tuto5 = false;
				Tuto5 = GetTickCount64();
			}
		}

		if (!tuto5 && tuto6)
		{
			if (Tuto5 + 5000 > GetTickCount64())
			{
				OnDrawText((char*)"제군, 멀지 않은 지점에 다수의 적기가 출현했다. 이건 훈련이 아니라 실제 상황이다.", 60 - strlen("제군, 멀지 않은 지점에 다수의 적기가 출현했다. 이건 훈련이 아니라 실제 상황이다.") / 2, Height + 1);
				OnDrawText((char*)"자네의 임무는 아군 비행대의 합류까지 시간을 끄는거다.", 60 - strlen("자네의 임무는 아군 비행대의 합류까지 시간을 끄는거다.") / 2, Height + 3);
				OnDrawText((char*)"적의 군세를 줄이되 절대 무리하지 말고 죽지말게. 이건 명령이야", 60 - strlen("적의 군세를 줄이되 절대 무리하지 말고 죽지말게. 이건 명령이야") / 2, Height + 5);
				OnDrawText((char*)"그럼, 건투를 빌겠다", 60 - strlen("그럼, 건투를 빌겠다") / 2, Height + 7);
			}
			if (Tuto5 + 5000 < GetTickCount64())
			{
				Tuto6 = GetTickCount64();
				tuto6 = false;
			}
		}

		if (!tuto6 && tuto7)
		{
			if (Tuto6 + 5000 > GetTickCount64())
			{
				OnDrawText((char*)"적기 격추시 500점, 미사일로 격추시 추가로 1500점을 획득합니다.", 60 - strlen("적기 격추시 500점, 미사일로 격추시 추가로 1500점을 획득합니다.") / 2, Height + 2, 14);
				OnDrawText((char*)"주기적으로 드랍되는 아이템은 전투에 직접적인 도움을 주거나 HP를 회복시켜 줍니다.", 60 - strlen("주기적으로 드랍되는 아이템은 전투에 직접적인 도움을 주거나 HP를 회복시켜 줍니다.") / 2, Height + 4, 14);
				OnDrawText((char*)"점수 결산시에 남은 HP에 비례한 추가 점수도 있으니 유의하고 전투에 임해주시기 바랍니다.", 60 - strlen("점수 결산시에 남은 HP에 비례한 추가 점수도 있으니 유의하고 전투에 임해주시기 바랍니다.") / 2, Height + 6, 14);
			}
			if (Tuto6 + 5000 < GetTickCount64())
			{
				Story = true;
				tuto6 = false;
				UI = false;
				if(_Player->TransInfo.Position.x > 60)
					while (_Player->TransInfo.Position.x < 60)
					{
						--_Player->TransInfo.Position.x;
						break;
					}
				if(_Player->TransInfo.Position.x < 60)
					while (_Player->TransInfo.Position.x < 60)
					{
						++_Player->TransInfo.Position.x;
						break;
					}					
				if (_Player->TransInfo.Position.y < 56)
					while (_Player->TransInfo.Position.y < 56)
					{
						++_Player->TransInfo.Position.y;
						break;
					}
				if (_Player->TransInfo.Position.x == 60 && _Player->TransInfo.Position.y == 56)
				{
					Story = false;
					Story1 = false;
					R1 = true;
				}
			}
		}

		if (tuto4)
		{
			if (!Check && GetAsyncKeyState(VK_SPACE) & 0x0001)
			{
				Check = true;
			}
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				if (Heat < 10)
					Heat += 0.25f;
				for (int i = 0; i < 128; ++i)
				{
					if (Bullet[i] == nullptr)
					{
						Bullet[i] = CreateBullet(
							_Player->TransInfo.Position.x - 2,
							_Player->TransInfo.Position.y + 1);
						Bullet[i + 1] = CreateBullet(
							_Player->TransInfo.Position.x + 2,
							_Player->TransInfo.Position.y + 1);
						break;
					}
				}
			}

			if (Check && !(GetAsyncKeyState(VK_SPACE) & 0x8000))
			{
				Check = false;
			}

			if (!Check)
			{
				if (Cooling1 + 500 < GetTickCount64())
				{
					Cooling1 = GetTickCount64();
					if (Heat > 0)
						Heat -= 1.0f;
					if (Heat < 0)
						Heat = 0;
				}
			}
		}
		for (int i = 0; i < 128; ++i)
		{
			if (Bullet[i] != nullptr)
			{
				for (int j = 0; j < 64; ++j)
				{
					if (_E1)
					{
						if (ECollision(Bullet[i], _E1))
						{
							E1V = false;

							delete Bullet[i];
							Bullet[i] = nullptr;

							break;
						}
					}
				}
				if (Bullet[i] != nullptr)
				{
					if (Bullet[i]->TransInfo.Position.y <= 0)
					{
						delete Bullet[i];
						Bullet[i] = nullptr;
					}
				}
			}
		}

		if (Load)
		{
			if (GetAsyncKeyState(0x58))
			{
				for (int i = 0; i < 8; ++i)
				{
					if (Missile[i] == nullptr)
					{
						Load = false;
						Missile[i] = CreateBullet(
							_Player->TransInfo.Position.x,
							_Player->TransInfo.Position.y - 1);
						Missile[i]->Missile.MTime = GetTickCount64();
						Missile[i]->Speed = 0;
						Missile[i]->HP = 3;
						Loaded1 = GetTickCount64();
						break;
					}
				}
			}
		}		

		for (int i = 0; i < 8; ++i)
		{
			if (Missile[i] != nullptr)
			{				
				if (_E2 != nullptr)
				{
					if (ECollision(Missile[i], _E2))
					{
						E2V = false;

						break;
					}
				}
				if (_E3 != nullptr)
				{
					if (ECollision(Missile[i], _E3))
					{
						E3V = false;

						break;
					}
				}
				if (Missile[i] != nullptr)
				{
					if (Missile[i]->TransInfo.Position.y <= 0)
					{
						delete Missile[i];
						Missile[i] = nullptr;
					}
				}
			}
		}

		for (int i = 0; i < 8; ++i)
		{
			if (Missile[i])
			{
				OnDrawText(Missile[i]->Missile.Texture[0],
					Missile[i]->TransInfo.Position.x,
					Missile[i]->TransInfo.Position.y, 10);

				if (Missile[i]->Missile.MTime + 500 < GetTickCount64())
				{
					Missile[i]->Missile.MTime = GetTickCount64();
					Missile[i]->Speed += 1.5f;
				}
				Missile[i]->TransInfo.Position.y -= Missile[i]->Speed;
			}
		}

		for (int i = 0; i < 256; ++i)
		{
			if (Bullet[i])
			{
				OnDrawText(Bullet[i]->Bullet.Texture,
					Bullet[i]->TransInfo.Position.x,
					Bullet[i]->TransInfo.Position.y, 14);

				Bullet[i]->TransInfo.Position.y -= 1.5f;
			}
		}

		if (!Story)
			UpdateInput1(_Player);

		if(!first)
			OnDrawObj(_Player, _Player->TransInfo.Position.x, _Player->TransInfo.Position.y);
		if(E1V)
			OnDrawObj(_E1, _E1->TransInfo.Position.x, _E1->TransInfo.Position.y);

		if(E2V)
			OnDrawObj(_E2, _E2->TransInfo.Position.x, _E2->TransInfo.Position.y);
		if(E3V)
			OnDrawObj(_E3, _E3->TransInfo.Position.x, _E3->TransInfo.Position.y);

		if (!tuto4 && tuto5)
		{
			if (!Load)
			{
				if (Loaded1 - GetTickCount64() >= -999)
					OnDrawText(5, 113.0f, 1.0f, 14);
				else if (Loaded1 - GetTickCount64() >= -1999)
					OnDrawText(4, 113.0f, 1.0f, 14);
				else if (Loaded1 - GetTickCount64() >= -2999)
					OnDrawText(3, 113.0f, 1.0f, 14);
				else if (Loaded1 - GetTickCount64() >= -3999)
					OnDrawText(2, 113.0f, 1.0f, 14);
				else if (Loaded1 - GetTickCount64() >= -4999)
					OnDrawText(1, 113.0f, 1.0f, 14);
				else if (Loaded1 - GetTickCount64() <= -5000 &&
					Loaded1 - GetTickCount64() >= -5049)
					Load = true;
			}
		}
		
		if (!tuto4 && tuto5)
		{
			if (Loaded1 - GetTickCount64() <= -5000)
				OnDrawText((char*)"Loaded", 111.0f, 1.0f, 10);
		}		

		
		if(!tuto4 && tuto5)
			OnDrawText((char*)"Missile : ", 101.0f, 1.0f);

		if (!tuto3 && tuto4)
			OnDrawText((char*)"Heat Gauge : [                    ]", 84.0f, 0.0f);

		if (tuto4)
		{
			for (int i = 0; i < Heat; ++i)
			{
				OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 10);
				if (7.9f >= Heat && Heat >= 5.0f)
				{
					ERR1 = GetTickCount64();
					OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 14);
				}

				if (9.9f >= Heat && Heat >= 8.0f)
				{
					ERR1 = GetTickCount64();
					OnDrawText((char*)"■", 98.0f + i * 2, 0.0f, 12);
				}
				if (Heat >= 10.0f)
				{
					OHeat = true;
					OnDrawText((char*)"[ O V E R H E A T ! !]", 97.0f, 0.0f, 12);

					if (ERR1 + 3000 < GetTickCount64())
					{
						ERR1 = GetTickCount64();
						OHeat = false;
						Heat = 0.0f;
					}

				}
			}
		}		
	}
	
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

void UpdateInput1(Object* _Object)
{
	if (_Object->TransInfo.Position.y >= 20)
	{
		if (GetAsyncKeyState(VK_UP))
			_Object->TransInfo.Position.y -= 1;
	}
	
	if (_Object->TransInfo.Position.y < 45)
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

void Warning(const int _x, const int _y)
{
	for (int i = 0; i + _y < 50; ++i)
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

void Warning2(const int _y)
{
	/*int Width1 = 60 - strlen("   / / /  | |     / /   |  / __ \/ | / /  _/ | / / ____/  / / /") / 2;

	OnDrawText((char*)"    ____   _       _____    ____  _   _______   ________   ____", Width1 , _y + 20, 12);
	OnDrawText((char*)"   / / /  | |     / /   |  / __ \/ | / /  _/ | / / ____/  / / /", Width1 , _y + 21, 12);
	OnDrawText((char*)"  / / /   | | /| / / /| | / /_/ /  |/ // //  |/ / / __   / / / ", Width1 , _y + 22, 12);
	OnDrawText((char*)" /_/_/    | |/ |/ / ___ |/ _, _/ /|  // // /|  / /_/ /  /_/_/  ", Width1 , _y + 23, 12);
	OnDrawText((char*)"(_|_)     |__/|__/_/  |_/_/ |_/_/ |_/___/_/ |_/\____/  (_|_)   ", Width1 , _y + 24, 12);
	*/
	int Width = 60 - strlen("========================================================================================================================") / 2;
	                 
	OnDrawText((char*)"========================================================================================================================", Width, _y, 12);
	OnDrawText((char*)"=========  ==  =======  ====  ====  =====  =====       ===  =======  ==    ==  =======  ===      ========  ==  =========", Width, _y + 1, 12);
	OnDrawText((char*)"=========  ==  =======  ====  ====  ====    ====  ====  ==   ======  ===  ===   ======  ==   ==   =======  ==  =========", Width, _y + 2, 12);
	OnDrawText((char*)"=========  ==  =======  ====  ====  ===  ==  ===  ====  ==    =====  ===  ===    =====  ==  ====  =======  ==  =========", Width, _y + 3, 12);
	OnDrawText((char*)"=========  ==  =======  ====  ====  ==  ====  ==  ===   ==  ==  ===  ===  ===  ==  ===  ==  =============  ==  =========", Width, _y + 4, 12);
	OnDrawText((char*)"=========  ==  =======   ==    ==  ===  ====  ==      ====  ===  ==  ===  ===  ===  ==  ==  =============  ==  =========", Width, _y + 5, 12);
	OnDrawText((char*)"=========  ==  ========  ==    ==  ===        ==  ====  ==  ====  =  ===  ===  ====  =  ==  ===   =======  ==  =========", Width, _y + 6, 12);
	OnDrawText((char*)"=======================  ==    ==  ===  ====  ==  ====  ==  =====    ===  ===  =====    ==  ====  ======================", Width, _y + 7, 12);
	OnDrawText((char*)"=========  ==  =========    ==    ====  ====  ==  ====  ==  ======   ===  ===  ======   ==   ==   =======  ==  =========", Width, _y + 8, 12);
	OnDrawText((char*)"=========  ==  ==========  ====  =====  ====  ==  ====  ==  =======  ==    ==  =======  ===      ========  ==  =========", Width, _y + 9, 12);
	OnDrawText((char*)"========================================================================================================================", Width, _y + 10, 12);
    
}

void BossScene()
{
	float Width = 5.0f;
	float Height = 2.0f;

	OnDrawText((char*)"MMMMFVVVVFVVIMMMMMMMMMMNMNNMNNMMMMMNNNNNUUUUU******VVVUUVVV*****VUVFIMMMMMIFIMMMIFFFIIIIVVVVFVVVNNMMMNNMMVMNNM", Width, Height, 6);
	OnDrawText((char*)"MMM::.:.::.:::::.:::..:****:::..:****:::I**VNBF*****VVUUVV*****VFFF*::::*::*:::::*****:::**::*********:****MMM", Width, Height + 1, 6);
	OnDrawText((char*)"MMM::*********::::::.:::***:::..:**:::*:IVVVVFFV*****VVVV*****VVFIII:..::**::::******:::::::**:***********VMMM", Width, Height + 2, 6);
	OnDrawText((char*)" MMMVM*::**::*****::::::*****:..::***:**IVFVVVVVI*****VV*****NBVFIII**:****::::*******:::*******:******NNVMNM ", Width, Height + 3, 6);
	OnDrawText((char*)"      NN************:******V**:::*******IIVVVVIIIV**********VVVVVIIV********:::*VVV**************VVFFIIM      ", Width, Height + 4, 6);
	OnDrawText((char*)"        NMMMFVVVV***::******************IVIVVVFVFVV********IVVVVVIIM:.*V*******V*********VVVFIIIMMMNNN        ", Width, Height + 5, 6);
	OnDrawText((char*)"              NNNM*VVVVVVV*NNNVVFVVFFF**BNFFVVFFFVVV******IFVVIVFIII**VV*NFVVFF*VVVVFVVVVV:MNNNN              ", Width, Height + 6, 6);
	OnDrawText((char*)"                 LNFNNMFIIIIUUBUUFUUVVVUUUVFVVVVFFVVV****VIFFVVVFIMIUUUVUVUUUUU*VMIIIIUFUUUN/                 ", Width, Height + 7, 6);
	OnDrawText((char*)"                      IIIIIIII    IIIIIIII  FVVV   VVV**VVV   VVFV  IIIIIIII    IIIIIIII                      ", Width, Height + 8, 6);
	OnDrawText((char*)"                      VVIIIIVV    VVIIIIVV  VVFI    VVVVVV    FVVF  VVIIIIVV    VVIIIIVV                      ", Width, Height + 9, 6);
	OnDrawText((char*)"                       VIIIIV     VVIIIIVV  NIFVV    UUUU    VFFNF  VVIIIIVV     VIIIIV                       ", Width, Height + 10, 6);
	OnDrawText((char*)"                       VVIIVV      VVIIVV    VVVVV    II    VVMVV    VVIIVV      VVIIVV                       ", Width, Height + 11, 6);
	OnDrawText((char*)"                        VVVV       VVIIVV     FMVVV        VVMVV     VVIIVV       VVVV                        ", Width, Height + 12, 6);
	OnDrawText((char*)"                                    VVVV       FMFVV      VFNVV       VVVV                                    ", Width, Height + 13, 6);
	OnDrawText((char*)"                                                VMIVV    VVVVV                                                ", Width, Height + 14, 6);
	OnDrawText((char*)"                                                 VVVVVVVVVVVV                                                 ", Width, Height + 15, 6);
	OnDrawText((char*)"                                                  VUUUUUUUUV                                                  ", Width, Height + 16, 6);
	OnDrawText((char*)"                                                   VUUUUUUV                                                   ", Width, Height + 17, 6);
	OnDrawText((char*)"                                                     VUUV                                                     ", Width, Height + 18, 6);


	OnDrawText((char*)"**", 54, Height + 8, 12);
	OnDrawText((char*)"**", 64, Height + 8, 12);
	OnDrawText((char*)"***", 54, Height + 9, 12);
	OnDrawText((char*)"***", 63, Height + 9, 12);
	OnDrawText((char*)"***", 55, Height + 10, 12);
	OnDrawText((char*)"***", 62, Height + 10, 12);
	OnDrawText((char*)"***", 56, Height + 11, 12);
	OnDrawText((char*)"***", 61, Height + 11, 12);
	OnDrawText((char*)"**::**", 57, Height + 12, 12);
	OnDrawText((char*)"****", 58, Height + 13, 12);
	OnDrawText((char*)"**", 59, Height + 14, 12);
	OnDrawText((char*)"VV", 7, Height + 4, 13);
	OnDrawText((char*)"VV", 111, Height + 4, 13);
	OnDrawText((char*)"VV", 15, Height + 6, 13);
	OnDrawText((char*)"VV", 103, Height + 6, 13);
	OnDrawText((char*)"VV", 24, Height + 8, 13);
	OnDrawText((char*)"VV", 36, Height + 8, 13);
	OnDrawText((char*)"VV", 82, Height + 8, 13);
	OnDrawText((char*)"VV", 94, Height + 8, 13);
}

void BossTuto()
{
	int Width = 60 - strlen("┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒") / 2;
	int Height = 12;
	OnDrawText((char*)"┎ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┒", Width, Height, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 1, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 2, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 3, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 4, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 5, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 6, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 7, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 8, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 9, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 10, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 11, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 12, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 13, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 14, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 15, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 16, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 17, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 18, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 19, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 20, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 21, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 22, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 23, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 24, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 25, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 26, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 27, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 28, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 29, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 30, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 31, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 32, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 33, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 34, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 35, 14);
	OnDrawText((char*)"ㅣ                                                                                                         ㅣ", Width, Height + 36, 14);
	OnDrawText((char*)"┖ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┚", Width, Height + 37, 14);


	OnDrawText((char*)"확인하고 전투 시작 [ SPACE BAR ]", 60 - strlen("확인하고 전투 시작 [ SPACE BAR ]") / 2, Height + 35, 11);
}