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

struct Bullet
{
	char* Texture = (char*)"¡«";
};

struct Missile
{
	char* Texture = (char*)"¥Ë";
	ULONGLONG MTime;
};

struct Item
{
	char* Texture[2] = { nullptr };
	int Color = 10;
	int Option;
};

struct Object
{
	Player Player;
	Enemy Enemy;
	Bullet Bullet;
	Missile Missile;
	Item Item;
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


//struct Boss
//{
//	char* Texture[17] = { (char*)"MMMMMMMMMMNNMNNMNNVVMMMNNNMMNNVVMMMVMMVMMVVNMVVVIMF*MVI*MMMMMVNMNFFVVVMMMNMMNNNMNMMMMMMMIIMMIIVVVVVVVIVVIMMM",
//						  (char*)"MMV**:*:***::***:.*::::*****:::..****:::**MIMIM*VM*VF:NVVN VF*VIMM**:..::*:.....****::.:*:.:*VV**VVV**V*V*MM",
//						  (char*)"MMV*VVFVMMIVVMV**::*.::*V***.:..:*V*:::*:VIMF:FMI*.*I*M*:M IV:*NN F.:::*V*:..::*VVV*:*:::::*:*IIVVVFVIVV*VMM",
//						  (char*)"VVNNV*V***V*:*VVV**:.::::VVIV*...:*FV*:**NINV*F VVV**M**V  M**F N F*:*VIV*:..*VIMV*::*:**VVIFV:*:V***VVVNNVV",
//						  (char*)"    NMNMMIVV*****VVV*****IIMF*:::*VVVMV**VMV*FIMVNV*****M NI*VFVMNIVVNFVVV**:*FNIMFVVV*VV****VVFINNMMNNN    ",
//						  (char*)"    VV    VV    VMMFV**VV***VNVVV****NF*V NINNIM  M*FVM*N  MVNNMN I.:MI*VVVNVIV*:*VVVV*MNNNV    VV    VV    ",
//						  (char*)"                VV *MM  NMIFVV***VVVIMF**M MF M   V:*VV*V   INMM  MVMMIVV**V*VVIMN NN M *FVV                ",
//						  (char*)"                       MM   NMMIMIFVVVVI*V MIMM  NVFMNNNF   MIMN  FVIFFIMM  FNVNNN NMN                      ",
//						  (char*)"                        VM*MN*M     MMMNMVNMVV*M IFNVNMMNI  IV**MNV NMNN NN  M*NIVIVV                       ",
//						  (char*)"                       I*MVVMM     MI NMNINFVI   MVV*NIFMM    F*INFNNM NMMN NNN M*MIV                       ",
//						  (char*)"                       MVMNVIM     V*N*MI   IVVVV*V**VVNVVVVVFVM    N*IVV       IVMNV                       ",
//						  (char*)"                       NFMNFIN     VV FVM     MIIIVIIVVNV*IVVM      I* NV       MMINVM                      ",
//						  (char*)"                       NVMMI*N     VFM I        MFFVMM M*MFM        IIMNM       VNIM*M                      ",
//						  (char*)"                                   VMMNFV       MMV:IMMV*VMN        VMMNVF                                  ",
//						  (char*)"                                                 MNV*VMVV                                                   ",
//						  (char*)"                                                    NVVI                                                    " };
//			
//	int HP;
//	Transform TransInfo;
//	HitBox HitZone;
//};
//
//struct HitBox
//{
//	char* Texture = (char*)"MMMM";
//	int Color = 12;
//	Transform TransInfo;
//};

struct Logo
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