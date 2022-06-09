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

struct Icon
{
	char* Texture = (char*)"=>-";
	Transform TransInfo;
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

struct sBullet
{
	char* Texture = (char*)"¡«";
};

struct sMissile
{
	char* Texture[2] = { (char*)"¥Ë", (char*)"¢£" };
	ULONGLONG MTime;
};

struct sItem
{
	char* Texture[2] = { nullptr };
	int Color = 10;
	int Option;
};

struct Hitbox
{
	char* Texture = (char*)"HHHH";
	ULONGLONG HTime;
	Transform TransInfo;
};

struct BOSS
{
	Hitbox Hitbox;
	int HP = 60;
};

struct Object
{
	Icon Icon;
	Player Player;
	Enemy Enemy;
	sBullet Bullet;
	sMissile Missile;
	sItem Item;
	Transform TransInfo;
	int Speed;
	int HP;
};

struct BackGround
{
	char* Texture;
	int Color;
	Transform TransInfo;
};

struct sLogo
{
	char* Texture[40] = { (char*)"                                                                                               MVV * M                 ",
						(char*)"                                                                                             NVV*FN                     ",
						(char*)"                                                                                            FVV*M                       ",
						(char*)"                                                     NMMIIFIMMNN                          MVV**N                        ",
						(char*)"                                                    NVVVVVVVVV*****VFMN                 NFVV*V                          ",
						(char*)"                                                    IVVFVVVVVVV**:::**VVFM            NFVV**M                           ",
						(char*)"                                                    FVVVVVVVVVVVVV*::VVVVFM         NIVV*:*N                            ",
						(char*)"                                                    FFVVVVVVVVVVVVVVVFVFN          MVVV*:*                              ",
						(char*)"                                                   NVVVV****VVVV****VIIFMN       IVVV*::*                               ",
						(char*)"                                                  FV****VVVVVVVVVVVVFIIIFFIMNNMIVVVV***VVFN                             ",
						(char*)"                                                  V*:VVVFFFFIIFFFFFFVVVVVFMMFVVVVVVVVVVVVFN                             ",
						(char*)"                                                  F**VFFFFIMMMIFFVVVVVFIMMMV::VVVVVVVVVFM                               ",
						(char*)"                                                  IFIIIIFVVFIFFVV***VIMMIIN*:*VVVVVVVVFN                                ",
						(char*)"                                                 IFIIIFVVVVVFVVVVVVFVVVVVVV**VVVVVVFVVFN    NMMIIMN                     ",
						(char*)"                                               MIVVVV****VVVFVVVVVVVVVVVVVVVVVFIIVVV*VVVVMMV**::::*M                    ",
						(char*)"                                            NMIFV*****VVVVFIFVVVVVVVVVVVVVVVIMFVVVVVVVVFV******::::VN                   ",
						(char*)"                                          NMMMMFV**VVVVFMMMMIVVVVVVVVVVVVFIMIFVVVVVVVVV*:::***VV:::*N                   ",
						(char*)"                                         NMMNMMVFFIIMMMMMMIFVMFVVVVV*VVVV*VVVV*::**VVVVV*:VFIVVVVV*V   NFVVVN           ",
						(char*)"                                        NMNNNMMIMMMMMMMMMFVVFMFVIIVVV***VVVVVVVVVVFVVFFFIFFFVVV***VVVF*::::::VM         ",
						(char*)"                                       MMMMMFVV***IMMMMMVVVVMMIVV**:::.::VVVVVVVVVV*VFMMIVVVVVV*::*VVVV*:::::::*M       ",
						(char*)"                                     NMFFF***:::*VMMMIVVVVVFVV*::::..:::*VVVVVVVVVVVVVVVVVVVVVVV***VVVVVV**::::::V      ",
						(char*)"                                  NMFVV**:*:::**IMIVVVVVFFVV*:::::::.:*VFVVVVVVVVVVVVVVVVVVVVVVVV*:VVVVVVVVV**::::VN    ",
						(char*)"                                NIFV**:..::V*VFFVVVVVVVVFFVVVVV**:::::VIVVVVVVVVVVVVVVVVVVVVVVV*::*VVVVVVVVVVVV**VVVM   ",
						(char*)"                              NIVV*:...:**VFVV*VVVVVVVFIIMMMIFFVVVV**VVVVVVVVVVVVVVVVVVVVVVV*:::*VVVVVVVVVVVVVVVVVVVVIN ",
						(char*)"                            MFVVV:...:*VVV***VVVVVVVVIMMMMMMMMMMMIV*VVVVVVVVVV******:::::***:**VVVVVVVVVVVVVVVVVVVVVVVVN",
						(char*)"                          MVV**:**:*VVV****VVVVVVVVIMMIIMMMMMMMIV**VVVVVVVVVFFFFVVVVV**V:..:**VVVVV**V*VVVVVVVVVVVVVVVFN",
						(char*)"                       NNIV**:.:*VVV****VVVVVVVVVFFIIIIIIIIIIF***V***VVIMNN         NIMIFVVVVMN    NNMMIIIFVVVVVVVVVFN  ",
						(char*)"                     NMIVV*:**VV*****VVVVVVFFFVFFFFVVVVVVVVVVVVIMMNN               MMIMMMMM                             ",
						(char*)"                  NNMMF*VIIFVV*:**VVVVVVVFFFVVVIMMMMMMMMMMMIM                    NMIIMMIMN                              ",
						(char*)"                NMMMMMMIFV*::**VVVVVFFFFIMN MMMMMMIMMMIMMMN                      MM                                     ",
						(char*)"             NMMMMMMIFV*::**VVVVFFVVIMM       NIFIMNMMN                                                                 ",
						(char*)"           NMMMMMMFV*::**VVVVVVVVVIN          NN                                                                        ",
						(char*)"         MMMMMMIV*::**VVVFFFFFIMN                                                                                       ",
						(char*)"       MMMMMMV****VVVVFFFFIMN                                                                                           ",
						(char*)"     MMMMMIV***VVVVFFFIMMN                                                                                              ",
						(char*)"   NVVMIFV**VVVVVFFFIMN                                                                                                 ",
						(char*)"  M*::**VVVVVFFIFFIN                                                                                                    ",
						(char*)"NV:....*VVFIIINNN                                                                                                       ",
						(char*)"M*::*::*VIMNN                                                                                                           ",
						(char*)" MMMVNMIN                                                                                                               " };
};																																										  