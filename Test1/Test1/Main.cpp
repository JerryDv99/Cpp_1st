#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>

const int Scene_Logo = 0;
const int Scene_Main = 1;
const int Scene_Story = 2;
const int Scene_Stage = 3;
const int Scene_Ending = 4;
const int Scene_Exit = 5;

int SceneState = 0;

int i = 0;
int turn = 0;

typedef struct sInfo
{
	int HP;
	int MP;

	int ATK;
	int DEF;

	int Level;
	int Speed;

	int EXP;
	int Gold;

} INFO;

typedef struct tagObject
{
	char* Name;
	INFO Info;
} OBJECT;

typedef struct Buff
{
	int ATKBF;
	int DEFBF;

	int EXPBF;
	int GoldBF;

}BUFF;

typedef struct Shop
{
	int Sword;
	int Armor;

	int Shoes;
	int Amulet;

}SHOP;

char* SetName();
void InitializePlayer(OBJECT* _Obj);
void InitializeEnemy1(OBJECT* _Obj);
void InitializeEnemy2(OBJECT* _Obj);
void InitializeEnemy3(OBJECT* _Obj);
void InitializeEnemy4(OBJECT* _Obj);
void InitializeEnemy5(OBJECT* _Obj);

void SceneManager(OBJECT* _Player, OBJECT* _Enemy1, OBJECT* _Enemy2, OBJECT* _Enemy3, OBJECT* _Enemy4, OBJECT* _Enemy5);

void LogoScene();
int MainScene();
void StoryScene();
void Tutorial(OBJECT* _Enemy);
void StageScene(OBJECT* _Player, OBJECT* _Enemy1, OBJECT* _Enemy2, OBJECT* _Enemy3, OBJECT* _Enemy4, OBJECT* _Enemy5);
int Turn(OBJECT* _Player, OBJECT* _Enemy);
void PlayerAtk(OBJECT* _Player, OBJECT* _Enemy);
void EnemyAtk(OBJECT* _Enemy, OBJECT* _Player);
void PlayerSkill(OBJECT* _Player, OBJECT* _Enemy, int _skill);
void Parrying(OBJECT* _Player, OBJECT* _Enemy);
void BattleScene(OBJECT* _Player, OBJECT* _Enemy, int _buff);
void BattleResult(OBJECT* _Player, OBJECT* _Enemy);
void PlayerLvUp(OBJECT* _Player);
void PlayerScene(OBJECT* _Player);
void EnemyScene(OBJECT* _Enemy);
void PStatScene(OBJECT* _Player);
void EStatScene(OBJECT* _Enemy);

void ShopScene(OBJECT* _Player, int _str);
int BuffScene();
void EndingScene();
int FailScene(OBJECT* _Player);
void ExitScene();
void BossScene();

void SetPosition(int _x, int _y, char* _str, int _Color = 15);
void SetColor(int _Color);
void HideCursor();

int main(void)
{
	HideCursor();

	system("mode con:cols=120 lines=30");

	system("title 고길동 v0.3");

	//system("color 87");

	OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT));
	InitializePlayer(Player);

	OBJECT* Enemy1 = (OBJECT*)malloc(sizeof(OBJECT));
	OBJECT* Enemy2 = (OBJECT*)malloc(sizeof(OBJECT));
	OBJECT* Enemy3 = (OBJECT*)malloc(sizeof(OBJECT));
	OBJECT* Enemy4 = (OBJECT*)malloc(sizeof(OBJECT));
	OBJECT* Enemy5 = (OBJECT*)malloc(sizeof(OBJECT));

	InitializeEnemy1(Enemy1);
	InitializeEnemy2(Enemy2);
	InitializeEnemy3(Enemy3);
	InitializeEnemy4(Enemy4);
	InitializeEnemy5(Enemy5);

	SetPosition(10, 10, (char*)"ㄱ                                    ㄴ");
	SetPosition(15, 10, (char*)"안녕");

	//SceneManager(Player, Enemy1, Enemy2, Enemy3, Enemy4, Enemy5);
	//PStatScene(Player);
	//EStatScene(Enemy5);

	free(Player);
	free(Enemy1);
	free(Enemy2);
	free(Enemy3);
	free(Enemy4);
	free(Enemy5);

	return 0;
}

char* SetName()
{

	char Buffer[128] = "";

	SetPosition(42, 12, (char*)"당신의 이름은... : ");
	scanf("%s", Buffer);

	if (strcmp(Buffer, "고길동") == 0)
	{
		SetPosition(35, 14, (char*)"그래, 내가 바로 고씨 집안 차남 고길동이다\n");
	}
	else
		SetPosition(25, 14, (char*)"내 이름을 왜 멋대로 정하지? 할아버지께서 지어주신 내 이름은 고길동이다\n");

	Sleep(1500);
	char* pName = (char*)malloc(7);

	strcpy(pName, "고길동");

	return pName;
}

void InitializePlayer(OBJECT* _Player)
{
	_Player->Name = SetName();

	_Player->Info.HP = 200;
	_Player->Info.MP = 5;
	_Player->Info.ATK = 50;
	_Player->Info.DEF = 10;
	_Player->Info.Level = 1;
	_Player->Info.Speed = 3;
	_Player->Info.EXP = 0;
	_Player->Info.Gold = 5000;

}

void InitializeEnemy1(OBJECT* _Obj)
{
	_Obj->Name = (char*)"쌍문동 촉법소년";

	_Obj->Info.HP = 15;
	_Obj->Info.MP = 0;
	_Obj->Info.ATK = 3;
	_Obj->Info.DEF = 1;
	_Obj->Info.Level = 1;
	_Obj->Info.Speed = 1;
	_Obj->Info.EXP = 100;
	_Obj->Info.Gold = 1000;
}

void InitializeEnemy2(OBJECT* _Obj)
{
	_Obj->Name = (char*)"해골 사냥꾼";

	_Obj->Info.HP = 40;
	_Obj->Info.MP = 0;
	_Obj->Info.ATK = 10;
	_Obj->Info.DEF = 10;
	_Obj->Info.Level = 3;
	_Obj->Info.Speed = 3;
	_Obj->Info.EXP = 300;
	_Obj->Info.Gold = 2000;
}

void InitializeEnemy3(OBJECT* _Obj)
{
	_Obj->Name = (char*)"흑마법사 도X너";

	_Obj->Info.HP = 100;
	_Obj->Info.MP = 5;
	_Obj->Info.ATK = 30;
	_Obj->Info.DEF = 5;
	_Obj->Info.Level = 9;
	_Obj->Info.Speed = 3;
	_Obj->Info.EXP = 1000;
	_Obj->Info.Gold = 10000;
}

void InitializeEnemy4(OBJECT* _Obj)
{
	_Obj->Name = (char*)"해골 킹";

	_Obj->Info.HP = 300;
	_Obj->Info.MP = 5;
	_Obj->Info.ATK = 50;
	_Obj->Info.DEF = 10;
	_Obj->Info.Level = 30;
	_Obj->Info.Speed = 10;
	_Obj->Info.EXP = 1500;
	_Obj->Info.Gold = 30000;
}

void InitializeEnemy5(OBJECT* _Obj)
{
	_Obj->Name = (char*)"인성파탄공룡 X리";

	_Obj->Info.HP = 2222;
	_Obj->Info.MP = 22;
	_Obj->Info.ATK = 222;
	_Obj->Info.DEF = 22;
	_Obj->Info.Level = 222;
	_Obj->Info.Speed = 22;
	_Obj->Info.EXP = 2222;
	_Obj->Info.Gold = 222222;
}

void SceneManager(OBJECT* _Player, OBJECT* _Enemy1, OBJECT* _Enemy2, OBJECT* _Enemy3, OBJECT* _Enemy4, OBJECT* _Enemy5)
{
	switch (SceneState)
	{
	case Scene_Logo:
		LogoScene();

	case Scene_Main:
		MainScene();

	case Scene_Story:
		StoryScene();
		SceneState++;

	case Scene_Stage:
		StageScene(_Player, _Enemy1, _Enemy2, _Enemy3, _Enemy4, _Enemy5);

	case Scene_Ending:
		EndingScene();

	case Scene_Exit:
		ExitScene();
		break;
	}
}

void LogoScene()
{
	system("cls");
	int Width = 10;
	int Height = 0;

	SetPosition(Width, Height + 1, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&#GP555555555PGB&@@@@@@@@",10);
	SetPosition(Width, Height + 2, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&P55PPGGGGGGGGGPP555G#@@@@@",10);
	SetPosition(Width, Height + 3, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BJPGGGGGGGGGGGGGGGGGGP55B@@@",10);
	SetPosition(Width, Height + 4, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#?GGGGGGGGGGGGGGGGGGGGGGPYY&@",10);
	SetPosition(Width, Height + 5, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Y5GGGGGGGGGGGGGGGGGGGGGGGGP?&",10);
	SetPosition(Width, Height + 6, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?GGGGPPGGGGGGGGGGGGGGGGGGGGY5",10);
	SetPosition(Width, Height + 7, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#B#J5GGJJ77GGGGGGGGGGGGGGGGGGGP?",10);
	SetPosition(Width, Height + 8, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@5Y55YYGP~:~YGGGGGGGGGGGGGGGGGGGG?",10);
	SetPosition(Width, Height + 9, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@5YGGGP5J5GG55GP55JPGGGGGGGGGGGGG5Y",10);
	SetPosition(Width, Height + 10, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&@@@@@@&?GGGG5Y#@@@@PYP?~~!PYPGGGGGGGGGG?#",10);
	SetPosition(Width, Height + 11, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&BGPP55555555PP575GGGPJ#@@@@GJG!.!YB?PGGGGGGGGPJG@",10);
	SetPosition(Width, Height + 12, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#P555PPGGGGGGGGGGGPJ?5GGGGYPGP55GGGP5P5GGGGGGGGPJJ?B@",10);
	SetPosition(Width, Height + 13, (char*)"@@@@@@@@@@@@@@@@@@@@@@&GPPPPPB@@@@@@@@@&####&&5YPGGGGGGGGGGGGGGGGJBB?YGGGGGPGGGGGGGG55GGGG5JYY?G@YY@",10);
	SetPosition(Width, Height + 14, (char*)"@@@@@@@@@@@@@@@@@@@@&PY5PGGGP5YG@@@@@BGGB#&#J?PGGGGGGGGGGGGGGGGGGJ5G#P7YPGGGGGGGGGGP?5GGYJ5G&@@@B5&@",10);
	SetPosition(Width, Height + 15, (char*)"@@@@@@@@@@@@@@@@@@@#J5GGGGGGGGG5J&@BPG&@@@&Y5GGGGGGGGGPYJ5PP555PGG5P55PPYYY5PGGGGGGYP@@G?&@@@&BPB@@@",10);
	SetPosition(Width, Height + 16, (char*)"@@@@@@@@@@@@@@@@@@#?PGGGGGGGGGGGP?5G@@@@@@J5GGGGGGP55PPGB@@@@@#GY5GGGGGGGGP5YYY55YJY&@&?JPBGYJ#@@@@@",10);
	SetPosition(Width, Height + 17, (char*)"@@@@@@@@@@@@@@@@@@Y5GGGGGGGGGGGGYY&@@@@@@#?GGGGGPYP#@@@@@@@@@@@@@GJGGGGGGGGGGGPPPPGPJGY5GPPPGJB@@@@@",10);
	SetPosition(Width, Height + 18, (char*)"@@@@@@@@@@@@@@@@@B?GGGGGGGGGGGGYY@@@@@@@@@JPGGGPJ&@@@@@@@@@@@@@@@@GJGGGGGGGGGGGGGGGGG7JGGGGGGG?#@@@@",10);
	SetPosition(Width, Height + 19, (char*)"@@@@@@@@@@@@@@@@@55GGGGGGGGGGG5!#@@@@@@@@GJJGGGPY@@@@@@@@@@@@@@@@@&?GGGGGGGGGGGGGGGGG5GGGGGGGGPJ@@@@",10);
	SetPosition(Width, Height + 20, (char*)"@@@@@@@@@@@@@@@@@?GGGGGGGGGPY5!?&@@@@@@@5YGGGGG?G@@@@@@@@@@@@@@@@@PYGGGGGGGGGGGGGGGGGGGGGGGGGGG?#@@@",10);
	SetPosition(Width, Height + 21, (char*)"@@@@@@@@@@@@@@@@#JGGGGGGGGPY#@5P#@@@@@@&?GGPGGGJG@@@@@@@@@@@@@@@@&?GGGGGGGGGGGGGGGGGGGGGGGGGGGGYP@@@",10);
	SetPosition(Width, Height + 22, (char*)"@@@@@@@@@@@@@@@@#?P555555575GGYJBG5B@@@@5Y575?5YG@@@@@@@@@@@@@@@BJPGGGGGGGGGGGGGGGGGGGGGGGGGGGGJG@@@",10);
	SetPosition(Width, Height + 23, (char*)"BPBGGBB#@@@@BPYJJ7J5PPPPPPPPPPGY5Y?J5GB@@#GP5B@@@@@@@@@@@@@@@#P55GGGGGGGGGGGGPP5YPGGGGGGGGGGGGPJ@@@@",10);
	SetPosition(Width, Height + 24, (char*)"?&@@&&#B5JGY?Y5PGGGGGGGGGGGGGGGGGGGGGP5YG&@@@@@@@@@@@@@@@&BP55PGGGGGGGGGGPP55Y5P5PY555555555555&@@@@",10);
	SetPosition(Width, Height + 25, (char*)"G5@@@@@@&?JPGGGGGGGGGGGGGGGGGGGGGGGGGGGGP55PPGBBBBBBGGPP555PGGGGGGGGGG5!JPGB&@@@@@&&#######&&@@@@@@@",10);
	SetPosition(Width, Height + 26, (char*)"@5G@@@@@@@YYGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGPPPPPPPPPPPGGGGGGGGGGGP5YYY555G@@@@@@@@@@@@@@@@@@@@@@@@@",10);
	SetPosition(Width, Height + 27, (char*)"@@5B@@@@@@@PYGGGGGGGGGGGGGGGGGGGGGGGGGGGGPGGGGGGGGGGGGGGGGGGPGP5YYY5GGGGGG5YG@@@@@@@@@@@@@@@@@@@@@@@",10);
	SetPosition(Width, Height + 28, (char*)"@@@GPB@@@@@@JPGGGGGGGGGGGGGGPPP55555Y5PP5?JPP555555555555555??J55PPPPPP55555J@@@@@@@@@@@@@@@@@@@@@@@",10);
	SetPosition(Width, Height + 29, (char*)"@@@@&BPP@@@@55GGGGGPP555555PPGB#####55PB#&@@@@@&&&&&&&&&&&&@@&BGGGGGBBB####&@@@@@@@@@@@@@@@@@@@@@@@@",10);
	Sleep(2000);
	system("cls");
	/*SetPosition(Width + 5, Height + 1, (char*)"@@@@@@@@@@@@@@@@@@@@GPPPPPPG&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 2, (char*)"@@@@@@#BB@@@@@@@@@@PPGGGGGGPPG&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 3, (char*)"@@@@@#GGJ#@@@@@@@@@5GPJ5GGGGGP5@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 4, (char*)"@@@@@@#YPP5&@@@@@@#5GP?Y5JJGGGY&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 5, (char*)"@@@@@@@B5GPP&@@@@@P5PJG@5YYGP5G@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 6, (char*)"@@@@@@@@5PGG5#@@@@@GJ55YPG55G#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 7, (char*)"@@@@@@@@#P5YP5&@@@@&P555PP5&@@@@@@@@@@@@@@@@@&BG&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 8, (char*)"@@@@@@@@&@&B#&&&&&#@@@&G##&@@@@@@@@@@@@@@@&BPJG#G#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 9, (char*)"@@@@@@&&@@&&&@@@&&#P#&&&@@@@@@@@@@@@@@@BGGPPPPB##&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 10, (char*)"@@@@@@&@@&@@@@@@@@&?7GP&&&&&&&@@@@@@@@#YGGGP5@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 11, (char*)"@&@@@@&@&&@@@@@&&#P5?~~P@@@&&&&&&&@@@@&5PPPB&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 12, (char*)"5PPG#@@&@@@@@B5?5B&@&G5Y&@@&@@&&&@@&@@@&GG@@@@@@@@@@BPP#@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 13, (char*)"B5GGPPGB&@@@@PG&@@@@@@&G5G###@@@@&@@@@@@@@@@@@@#5YPJ~^^!Y&@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 14, (char*)"@&PPGGJ!B&@@@G#@@@@@@@@&GPP5?P@@@@@@@@@@@@@@@@@?^^^^~~~~^7&@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 15, (char*)"@@@#GGYG@#@@@@P@@@@@@@@@&GGG7~B@@@@@@@@@@&##&&B7?5BGJ~~~~^Y@@@@@@@@@@@@@@@@@@#BB");
	SetPosition(Width + 5, Height + 16, (char*)"@@@@@@@@@&&@@@G&@@@@@@@@@&GGP?Y@@@@@@@@@B#@&#GPG@@G&@BJ~~~!&@@@@@@@@@@@@@&#BG#&@");
	SetPosition(Width + 5, Height + 17, (char*)"@@@@@@@@@@&&@@G&@@@@@@@@@@GGGPP@@@@@@@@@G@@@@@GB&&PPP#BP?^7@@@@@@@@@@@&#BB##@@@@");
	SetPosition(Width + 5, Height + 18, (char*)"@@@@@@@@@@@@&@&G&@@@@@@@@@GGP5@@@@@@@@@@B&@@&BBBGGYG#&#B@5G@@@@@@@&&&GBBB@@@@@@@");
	SetPosition(Width + 5, Height + 19, (char*)"@@@@@@@@&BPG#&@&P5#@@@@@@&GPG&@@@@@@@@@@&B@@@P5BGBP#@@B&@@@@@@&&######&@@@@@@@@@");
	SetPosition(Width + 5, Height + 20, (char*)"@@@@@@BPPPP5YB&@@&BP#&@&&GGPB@@@@@@@@@@@@BG@@BG&&@@B##@@@&&#######&&@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 21, (char*)"@@@&BGYPGPGB&&@&@@@@###BPPGG5#@@@@@@@&@@@BBB&@@##&#PPB&#####&#&&@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 22, (char*)"@@@GPPGPPP@@@@@@&@@@@@@@@P5GG5#@@@@@&BB@&B&BP#@@BB&PGP##&&&@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 23, (char*)"@@@@@@@@&@@@@@@@@@@@@@@@@@G5GP5@@@@@B@G#&B@@@##BPGBGPB&@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 24, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@GPGPPG@@#&@P##G#@@@@&P#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 25, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&@@B@#G@@GB#@@@@&B@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 26, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&B&B@B@@@##@@@@&B@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 27, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@B#@@@B&@@G#@@@@&B@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	SetPosition(Width + 5, Height + 28, (char*)"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##B&&#@@@@&#@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	Sleep(3000);
	system("cls");*/
	SetPosition(Width + 5, Height + 1, (char*)"                    ~!!!!!!~.",12);
	SetPosition(Width + 5, Height + 2, (char*)"      :^^          !!~~~~~~!!~.",12);
	SetPosition(Width + 5, Height + 3, (char*)"     :~~J:         7~!J7~~~~~!7",12);
	SetPosition(Width + 5, Height + 4, (char*)"      :?!!7.      :7~!Y?7JJ~~~?.",12);
	SetPosition(Width + 5, Height + 5, (char*)"       ^7~!!.     !7!J~ 7??~!7~",12);
	SetPosition(Width + 5, Height + 6, (char*)"        7!~~7:     ~J77?!~77~:",12);
	SetPosition(Width + 5, Height + 7, (char*)"        :!7?!7.    .!777!!7.                 .^~.",12);
	SetPosition(Width + 5, Height + 8, (char*)"        . .^:.....:   .~::.               .^!J~:~:",12);
	SetPosition(Width + 5, Height + 9, (char*)"      ..  ...   ..:!:...               ^~~!!!!^::.",12);
	SetPosition(Width + 5, Height + 10, (char*)"      .  .        .Y5~!.......        :?~~~!7",12);
	SetPosition(Width + 5, Height + 11, (char*)" .    . ..     ..:!7YGG!   .......    .7!!!^.",12);
	SetPosition(Width + 5, Height + 12, (char*)"7!!~:  .     ^7Y7^. .~7?.  .  ...  .   .~~          ^!!:",12);
	SetPosition(Width + 5, Height + 13, (char*)"^7~~!!~^.    !~.      .~7~:::    .             :7?!JGBBP?.",12);
	SetPosition(Width + 5, Height + 14, (char*)" .!!~~JP^.   ~:        .~!!7Y!                 YBBBBGGGGB5.",12);
	SetPosition(Width + 5, Height + 15, (char*)"   :~~?~ :    !         .~~~5G^          .::..^5Y7^~JGGGGB?                  :^^",12);
	SetPosition(Width + 5, Height + 16, (char*)"         ..   ~.         .~~!Y?         ^: .:~!~  ~. ^JGGGP.             .:^~:.",12);
	SetPosition(Width + 5, Height + 17, (char*)"          ..  ~.          ~~~!!         ~     ~^..!!!:^!YB5           .:^^::",12);
	SetPosition(Width + 5, Height + 18, (char*)"            . .~.         ~~!7          ^.  .^^^~~?~:.:^ 7~       ...~^^^",12);
	SetPosition(Width + 5, Height + 19, (char*)"        .^!~:. .!7:      .~!~.          .^   !7^~^!:  ^.      ..::::::.",12);
	SetPosition(Width + 5, Height + 20, (char*)"      ^!!!!7?^.  .^!:. ..~~!^            ^~  ^~..  ^::   ..:::::::..",12);
	SetPosition(Width + 5, Height + 21, (char*)"   .^~?!~!~^.. .    :::^!!~~7:       .   ^^^.  ::.:!!^.:::::.:..",12);
	SetPosition(Width + 5, Height + 22, (char*)"   ~!!~!!!      .        !7~~7:     .^^ .^.^!:  ^^.!~!::...",12);
	SetPosition(Width + 5, Height + 23, (char*)"        .                 ~7~!7     ^ ~:.^   ::^!~^~!^.",12);
	SetPosition(Width + 5, Height + 24, (char*)"                           ~!~!!~  :. !::~:    .!:",12);
	SetPosition(Width + 5, Height + 25, (char*)"                            .....  ^ :~  ~^:    .^",12);
	SetPosition(Width + 5, Height + 26, (char*)"                                  .^.^ ^   ::    .^",12);
	SetPosition(Width + 5, Height + 27, (char*)"                                   ^:   ^.  ~:    .^",12);
	SetPosition(Width + 5, Height + 28, (char*)"                                         ::^..:    .:",12);

										   
	Sleep(2000);

	SceneState++;
}

int MainScene()
{

	system("cls");
	int Width = 7;
	int MWidth = 47;
	int Height = 2;
	int MHeight = 20;
	int i = 0;

	SetPosition(Width, Height + 1, (char*)"                    ##                        ##                        ##",14);
	SetPosition(Width, Height + 2, (char*)"    ########        ##      ############      ##      ###########       ##        ################",14);
	SetPosition(Width, Height + 3, (char*)"  ###      ### #######           ##           ##              ##        ##        ##",14);
	SetPosition(Width, Height + 4, (char*)"  ##        ##      ##           ##           ##             ##         ##        ##  ",14);
	SetPosition(Width, Height + 5, (char*)"  ##        ##      ##          ####      ######           ###          ##        ################",14);
	SetPosition(Width, Height + 6, (char*)"  ###      ### #######        ###  ###        ##       ####             ##               ##",14);
	SetPosition(Width, Height + 7, (char*)"     ######         ##      ###      ###      ##      ##                ##    ########################",14);
	SetPosition(Width, Height + 8, (char*)"                                              ##",14);
	SetPosition(Width, Height + 9 , (char*)"      ################                       ##          ################          ############",14);
	SetPosition(Width, Height + 10, (char*)"                    ##          ##                                     ##         ###          ###   ",14);
	SetPosition(Width, Height + 11, (char*)"                    ##          ##                        ###############         ##            ##   ",14);
	SetPosition(Width, Height + 12, (char*)"                    ##          ##                        ##                      ###          ###",14);
	SetPosition(Width, Height + 13, (char*)"                    ##          ################          ################          ############",14);
	


	SetPosition(MWidth, MHeight - 1, (char*)"┌ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┐",11);
	SetPosition(MWidth, MHeight, (char*)"ㅣ                       ㅣ",11);
	SetPosition(MWidth, MHeight + 1, (char*)"ㅣ       메     뉴       ㅣ",11);
	SetPosition(MWidth, MHeight + 2, (char*)"ㅣ                       ㅣ",11);
	SetPosition(MWidth, MHeight + 3, (char*)"ㅣ       1. 플레이       ㅣ",11);
	SetPosition(MWidth, MHeight + 4, (char*)"ㅣ                       ㅣ",11);
	SetPosition(MWidth, MHeight + 5, (char*)"ㅣ       2. 종  료       ㅣ",11);
	SetPosition(MWidth, MHeight + 6, (char*)"ㅣ                       ㅣ",11);
	SetPosition(MWidth, MHeight + 7, (char*)"└ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┘",11);
	SetPosition(MWidth + 10, MHeight + 8, (char*)"입력 : ",11);
	scanf("%d", &i);
	Sleep(1000);
	SceneState++;

	return 1;
}

void StoryScene()
{
	system("cls");
	int Height = 5;

	SetPosition(49, Height, (char*)"'고길동 밥줘'",15);
	Sleep(800);
	SetPosition(21, Height + 2, (char*)"몇 년 전 딸아이가 주워온 그 녀석, 처음엔 불쌍해서 며칠 재워준단 생각이었지만");
	Sleep(800);
	SetPosition(11, Height + 4, (char*)"오자마자 집안의 물건을 다 부수더니 떠나긴 커녕 점점 패거리까지 늘었고 갈수록 패악질이 심해졌다.");
	Sleep(800);
	SetPosition(19, Height + 6, (char*)"'저...둘X야 이제 좀 나가주면 안되겠니?' '아잇! 초능력 맛 좀 볼래? 처신 잘 하라고'");
	Sleep(800);
	SetPosition(36, Height + 8, (char*)"이젠 나를 가정부 이하의 취급을 하는 녀석들...");
	Sleep(800);
	SetPosition(19, Height + 10, (char*)"기나긴 모멸과 핍박, 이제 인내의 시간은 끝났다. 창고로 가 봉인해둔 검을 집어든다.");
	Sleep(800);
	SetPosition(37, Height + 12, (char*)"아아... 이 서늘하고도 묵직한 감각... 2년만이군");
	Sleep(800);
	SetPosition(44, Height + 16, (char*)"'검성' 고길동으로 돌아갈 때다", 12);
	Sleep(3000);

	SceneState++;
}

void StageScene(OBJECT* _Player, OBJECT* _Enemy1, OBJECT* _Enemy2, OBJECT* _Enemy3, OBJECT* _Enemy4, OBJECT* _Enemy5)
{

	int i = 0;
	srand(time(NULL));
	Tutorial(_Enemy1);

	BattleScene(_Player, _Enemy1, i);
	if (rand() % 2 == 0)
		ShopScene(_Player, 1);
	else
		i = BuffScene();

	BattleScene(_Player, _Enemy2, i);
	if (rand() % 2 == 0)
		ShopScene(_Player, 2);
	else
		i = BuffScene();

	BattleScene(_Player, _Enemy3, i);
	if (rand() % 2 == 0)
		ShopScene(_Player, 3);
	else
		i = BuffScene();

	BattleScene(_Player, _Enemy4, i);
	if (rand() % 2 == 0)
		ShopScene(_Player, 4);
	else
		i = BuffScene();


	BattleScene(_Player, _Enemy5, i);
	SceneState++;
}

void Tutorial(OBJECT* _Enemy)
{
	system("cls");
	int Width = 30;
	int Height = 8;
	SetPosition(Width, Height, (char*)"오랜만의 실전인 만큼 그 때의 감각을 떠올릴 필요가 있겠어");
	Sleep(500);
	SetPosition(Width + 11, Height+1, ((char*)"야생의 "));
	SetPosition(Width + 11 + strlen("야생의"), Height+1, _Enemy->Name);
	SetPosition(Width + 11 + strlen("야생의") + strlen(_Enemy->Name), Height+1,"이(가) 나타났다!");

	Sleep(300);
	SetPosition(Width + 9, Height+2, (char*)"선빵필승! 속도가 빠른 쪽이 선공권을 가지지");
	Sleep(500);
	SetPosition(Width - 3, Height+3, (char*)"속도가 느려도 일반 공격 대신 스킬을 사용하면 먼저 공격할 수 있다");
	Sleep(500);
	SetPosition(Width - 17, Height+4, (char*)"스킬을 사용하기 위해 필요한 마나는 5를 가지고 시작하며, 매 턴이 끝나면 2의 마나를 추가로 얻는다");
	Sleep(500);
	SetPosition(Width + 21, Height+5, (char*)"자~ 드가자!");
}

void BattleScene(OBJECT* _Player, OBJECT* _Enemy, int _buff) 
{
	int i = 1;
	int exit = 0;
	int hp = _Player->Info.HP;
	int atk = _Player->Info.ATK;
	int def = _Player->Info.DEF;
	int spd = _Player->Info.Speed;
	if (_buff == 1)
	{
		_Player->Info.ATK *= 1.3;
	}
	else if (_buff == 2)
	{
		_Player->Info.DEF *= 1.3;
	}
	else if (_buff == 3)
	{
		_Player->Info.Speed += 10;
	}
	while (i)
	{
		int turn;
		for (turn = 1; _Player->Info.HP > 0 && _Enemy->Info.HP > 0; turn++)
		{
			exit = Turn(_Player, _Enemy);
			if (exit == 1)
			{
				_Player->Info.ATK = atk;
				_Player->Info.DEF = def;
				_Player->Info.Speed = spd;
				i = 0;
				break;
			}
		}
		_Player->Info.MP = 5;
		if(_Enemy->Info.HP <= 0)
		{
			_Player->Info.ATK = atk;
			_Player->Info.DEF = def;
			_Player->Info.Speed = spd;
			BattleResult(_Player, _Enemy);
			i = 0;
			break;
		}
		else if (_Player->Info.HP <= 0)
		{
			int j = FailScene(_Player);
			if (j == 1)
				_Player->Info.HP = hp;
			break;
		}
		
	}
	
	_buff = 0;
}

void PStatScene(OBJECT* _Player)
{
	int Width = 10;
	int Height = 40;
	SetPosition(Width, Height, _Player->Name);
	SetPosition(Width, Height + 1, (char*)_Player->Info.HP);
	SetPosition(Width, Height + 2, (char*)_Player->Info.MP);
	SetPosition(Width, Height + 3, (char*)_Player->Info.ATK);
	SetPosition(Width, Height + 4, (char*)_Player->Info.DEF);
	SetPosition(Width, Height + 5, (char*)_Player->Info.Level);
	SetPosition(Width, Height + 6, (char*)_Player->Info.Speed);
}

void EStatScene(OBJECT* _Enemy)
{
	int Width = 50;
	int Height = 40;
	SetPosition(Width, Height, _Enemy->Name);
	SetPosition(Width, Height + 1, (char*)_Enemy->Info.HP);
	SetPosition(Width, Height + 2, (char*)_Enemy->Info.MP);
	SetPosition(Width, Height + 3, (char*)_Enemy->Info.ATK);
	SetPosition(Width, Height + 4, (char*)_Enemy->Info.DEF);
	SetPosition(Width, Height + 5, (char*)_Enemy->Info.Level);
	SetPosition(Width, Height + 6, (char*)_Enemy->Info.Speed);
}

void PlayerAtk(OBJECT* _Player, OBJECT* _Enemy)
{
	if (_Player->Info.ATK > _Enemy->Info.DEF)
	{
		int dmg = _Player->Info.ATK - _Enemy->Info.DEF;
		printf_s("%s의 공격! %s은 %d의 데미지를 입었다\n", _Player->Name, _Enemy->Name, dmg);
		_Enemy->Info.HP -= dmg;
	}
	else
	{
		printf_s("%s의 공격은 그리 효과적이지 못했다, 1의 데미지를 입혔다\n", _Player->Name);
		_Enemy->Info.HP -= 1;
	}
}

void EnemyAtk(OBJECT* _Enemy, OBJECT* _Player)
{
	if (_Enemy->Info.ATK > _Player->Info.DEF)
	{
		int dmg = _Enemy->Info.ATK - _Player->Info.DEF;
		printf_s("%s의 공격! %s은 %d의 데미지를 입었다\n", _Enemy->Name, _Player->Name, dmg);
		_Player->Info.HP -= dmg;
	}
	else
	{
		printf_s("%s의 공격은 그리 효과적이지 못했다, 1의 데미지를 입혔다\n", _Enemy->Name);
		_Enemy->Info.HP -= 1;
	}
}


void PlayerSkill(OBJECT* _Player, OBJECT* _Enemy, int _skill)
{
	int s1 = _Player->Info.ATK * 2;
	int s3 = _Player->Info.ATK * 20;
	switch (_skill)
	{
	case 1:
		printf_s("하세기!\n");
		printf_s("%s에게 %d의 데미지를 입혔다\n", _Enemy->Name, s1 - _Enemy->Info.DEF);
		_Enemy->Info.HP -= s1;
		_Player->Info.MP -= 1;
		break;
	case 2:
		printf_s("");
		printf_s("%s이 방어자세를 취했다\n", _Player->Name);
		_Player->Info.MP -= 3;
		break;
	case 3:
		printf_s("울어라 지옥참마도\n");
		printf_s("%s에게 %d의 데미지를 입혔다\n", _Enemy->Name, s3 - _Enemy->Info.DEF);
		_Enemy->Info.HP -= s3;
		_Player->Info.MP -= 8;
		break;
	}
}

void Parrying(OBJECT* _Player, OBJECT* _Enemy)
{
	int s2 = _Player->Info.ATK;
	printf_s("%s이(가) 공격했지만 %s는 튕겨내고 반격했다! - %d\n", _Enemy->Name, _Player->Name, _Player->Info.ATK);
	_Enemy->Info.HP -= _Player->Info.ATK;
}

int Turn(OBJECT* _Player, OBJECT* _Enemy)
{
	int i = 0;
	int j = 0;
	int loop = 1;
	int turn = 1;
	int exit;

	PStatScene(_Player);
	EStatScene(_Enemy);

	while (loop)
	{
		
		printf_s("1.공격 2.스킬 3.도망\n");
		printf_s("나의 선택 : ");
		scanf("%d", &i);
		printf_s("\n");
		switch (i)
		{
		case 3:
			srand(time(NULL));
			if (_Enemy->Info.ATK == 222)
			{
				printf_s("이녀석은 존재해선 안된다");
				printf_s("내 손으로 마무리 짓겠어");
				i = 1;
			}
			else if (rand() % 2 == 0 && _Player->Info.Gold >= 1000) 
			{
				printf_s("바닥에 동전을 뿌려 적의 주의를 끄는데 성공했지만 1000원을 잃었다 ㅠㅠ");
				_Player->Info.Gold -= 1000;
				printf_s("현재 수중에 남은 돈 %d원", _Player->Info.Gold);
				exit = 1;
				loop = 0;
				break;
			}
			else if (rand() % 2 == 1 || _Player->Info.Gold <= 1000)
			{
				printf_s("아뿔싸, 들켜버렸군... %s은 하는 수 없이 전투태세를 취했다", _Player->Name);
				i = 1;
			}
		case 1:
			if (_Player->Info.Speed > _Enemy->Info.Speed)
			{
				printf_s("%d턴\n", turn);
				printf_s("%s의 선제공격 !\n", _Player->Name);

				PlayerAtk(_Player, _Enemy);
				if(_Enemy->Info.HP >= 0)
					EnemyAtk(_Enemy, _Player);

				_Player->Info.MP += 2;
				_Enemy->Info.MP += 2;
				PStatScene(_Player);
				EStatScene(_Enemy);
				exit = 0;
				turn++;
				break;
			}
			else if (_Player->Info.Speed < _Enemy->Info.Speed)
			{
				printf_s("%d턴\n", turn);
				printf_s("%s의 선제공격 !\n", _Enemy->Name);

				EnemyAtk(_Enemy, _Player);
				if(_Player->Info.HP >= 0)
					PlayerAtk(_Player, _Enemy);

				_Player->Info.MP += 2;
				_Enemy->Info.MP += 2;
				PStatScene(_Player);
				EStatScene(_Enemy);
				exit = 0;
				turn++;
				break;
			}
			else
			{
				srand(time(NULL));
				printf_s("둘의 실력이 비슷해 동전 던지기로 선공을 결정하기로 했다\n");
				if (rand() % 2 == 0)
				{
					printf_s("%d턴\n", turn);
					printf_s("%s의 선제공격 !\n", _Player->Name);

					PlayerAtk(_Player, _Enemy);
					if (_Enemy->Info.HP >= 0)
						EnemyAtk(_Enemy, _Player);

					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;
					PStatScene(_Player);
					EStatScene(_Enemy);

					exit = 0;
					turn++;
					break;
				}
				else
				{
					printf_s("%d턴\n", turn);
					printf_s("%s의 선제공격 !\n", _Enemy->Name);

					EnemyAtk(_Enemy, _Player);
					if(_Player->Info.HP >= 0)
						PlayerAtk(_Player, _Enemy);

					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;
					PStatScene(_Player);
					EStatScene(_Enemy);

					exit = 0;
					turn++;
					break;
				}
			}
			loop = 0;
			break;
		case 2:
			printf_s("1. 1스킬 : 적에게 200%% 의 데미지, 소모 마나 1\n");
			printf_s("2. 2스킬 : 적의 다음 공격을 튕겨내고 100%%의 방어 무시 데미지, 소모 마나 3\n");
			printf_s("3. 3스킬 : 필살기를 사용해 2000%% 데미지, 소모 마나 8\n");
			printf_s("이외의 아무 키 : 취소\n");
			scanf("%d", &j);
			if (j > 0 && j <= 3)
			{
				if (_Player->Info.MP >= 1 && j == 1)
				{
					printf_s("%d턴\n", turn);
					PlayerSkill(_Player, _Enemy, j);
					if (_Enemy->Info.HP >= 0)
						EnemyAtk(_Enemy, _Player);
					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;
					PStatScene(_Player);
					EStatScene(_Enemy);

					turn++;
					loop = 0;
				}
				else if (_Player->Info.MP >= 3 && j == 2)
				{
					printf_s("%d턴\n", turn);
					PlayerSkill(_Player, _Enemy, j);
					Parrying(_Player, _Enemy);
					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;
					PStatScene(_Player);
					EStatScene(_Enemy);

					turn++;
					loop = 0;
				}
				else if (_Player->Info.MP >= 8 && j == 3)
				{
					printf_s("%d턴\n", turn);
					PlayerSkill(_Player, _Enemy, j);
					if (_Enemy->Info.HP >= 0)
						EnemyAtk(_Enemy, _Player);
					_Player->Info.MP += 2;
					_Enemy->Info.MP += 2;
					PStatScene(_Player);
					EStatScene(_Enemy);

					turn++;
					loop = 0;
				}
				else
				{
					printf_s("마나가 부족합니다. 다시 선택하세요\n");
					break;
				}
			}
			else
				break;
			break;
		}
		if (_Player->Info.HP <= 0 || _Enemy->Info.HP <= 0)
		{
			loop = 0;
			break;
		}
	}

	return exit;
		
}

void BattleResult(OBJECT* _Player, OBJECT* _Enemy)
{
	printf_s("전투 승리! %s은(는) 흙으로 돌아갔다\n", _Enemy->Name);

	if ((_Player->Info.EXP += _Enemy->Info.EXP) < 100)
	{
		printf_s("경험치 %d 상승 ! 현재 경험치 %d\n", _Enemy->Info.EXP, _Player->Info.EXP);
	}
	else if ((_Player->Info.EXP += _Enemy->Info.EXP) >= 100)
	{
		int ex = ((_Player->Info.EXP += _Enemy->Info.EXP) % 100);
		for (int i = 0; i < ((_Player->Info.EXP += _Enemy->Info.EXP) / 100); i++)
		{
			PlayerLvUp(_Player);
		}
		printf_s("레벨 업! 현재 레벨 : %d Lv\n", _Player->Info.Level);
		_Player->Info.EXP = ex;
		printf_s("현재 경험치 : %dss\n", _Player->Info.EXP);
	}
}

void PlayerLvUp(OBJECT* _Player)	
{
	_Player->Info.HP += 80;
	_Player->Info.ATK += 20;
	_Player->Info.DEF += 5;
	_Player->Info.Level += 1;
	_Player->Info.Speed += 3;
	_Player->Info.EXP = 0;
}

int FailScene(OBJECT* _Player)
{
	int i = 0;

	printf_s("윽... 분하다\n");
	printf_s("재도전 하시겠습니까? 1을 입력해 1000원을 내고 재도전 , 이외의 키 입력으로 게임 종료\n");
	scanf("%d", &i);

	if (i == 1 && _Player->Info.Gold >= 1000)
	{
		i = 1;
		_Player->Info.Gold -= 1000;
	}
	else if (_Player->Info.Gold < 1000)
	{
		printf_s("지불할 금액이 부족하네요");
		printf_s("게임을 종료합니다.");
		exit(NULL);
	}
	else
	{
		printf_s("게임을 종료합니다.");
		exit(NULL);
	}
	return i;
}

void PlayerScene(OBJECT* _Player)
{

}


void EnemyScene(OBJECT* _Enemy)
{

}

void ShopScene(OBJECT* _Player, int _stg)
{
	int i = 0;

	int atk = 30;
	int def = 20;
	int hp = 50;
	int spd = 5;

	int w1 = 1500;
	int w2 = 500;
	int w3 = 1000;
	int w4 = 1000;

	printf_s("다음 전투를 위해 이동하던 중 방랑상인 마이콜을 만났다");
	printf_s("마이콜의 잡화상에 오신것을 환영합니다 길동아저씨, 같이 싸웠던 전우에겐 특별히 할인가로 드릴게요");
	printf_s("마이콜의 잡화상 : ");
	printf_s("1. 숯돌 : 공격력 %d 증가, %d원", _stg * atk, _stg * w1);
	printf_s("2. 후라이팬 : 방어력 %d 증가, %d원", _stg * def, _stg * w2);
	printf_s("3. 우황청심환 : 체력 %d 증가, %d원", _stg * hp, _stg * w3);
	printf_s("4. 슬리퍼 : 속도 %d 증가, %d원", _stg * atk, _stg * w4);
	printf_s("현재 소지금 : %d원, 구매를 원하지 않으면 1 ~ 4 이외의 키를 입력 : ", _Player->Info.Gold);
	scanf("%d", &i);
	
	if (i == 1)
	{
		_Player->Info.ATK += _stg * atk;
		_Player->Info.Gold -= _stg * w1;
	}
	else if (i == 2)
	{
		_Player->Info.DEF += _stg * def;
		_Player->Info.Gold -= _stg * w2;
	}
	else if (i == 3)
	{
		_Player->Info.HP += _stg * hp;
		_Player->Info.Gold -= _stg * w3;
	}
	else if (i == 4)
	{
		_Player->Info.Speed += _stg * spd;
		_Player->Info.Gold -= _stg * w4;
	}
	else
		i = 0;

	printf_s("감사합니다 호갱님!");
	printf_s("뭔가 찜찜하다... 현재 소지금 : %d원", _Player->Info.Gold);

}

int BuffScene()
{
	system("cls");
	int i = 0;
	int lp = 1;
	int Width = 39;

	while (lp)
	{
		SetPosition(Width, 7, (char*)"전투를 끝마친 당신을 희동이가 반겨준다");
		SetPosition(Width, 9, (char*)"희동이의 응원 : ");
		SetPosition(Width, 11, (char*)"1. 다음 전투에서 공격력 30% 증가 버프");
		SetPosition(Width, 13, (char*)"2. 다음 전투에서 방어력 30% 증가 버프");
		SetPosition(Width, 15, (char*)"3. 다음 전투에서 속도 10 증가 버프");
		SetPosition(Width, 17, (char*)"버프 선택 : ");
		scanf("%d", &i);
		if (i < 0 || i > 4)
		{
			SetPosition(Width + 9, 19, (char*)"다시 선택하세요");
			i = 0;
		}
		else
		{
			system("cls");
			SetPosition(Width + 11, 11, (char*)"고모부 힘내!");
			SetPosition(Width + 3, 15, (char*)"희동이의 응원에 힘이 솟는다");
			lp = 0;
		}
	}
	
	return i;
}

void BossScene()
{
	printf_s("ㄷ");
}

void EndingScene()
{
	printf_s("끝\n");
	SceneState++;
}

void ExitScene()
{
	printf_s("게임을 종료하시겠습니까?");
}

void SetPosition(int _x, int _y, char* _str, int _Color)
{
	COORD Pos = { _x, _y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	SetColor(_Color);

	printf_s("%s", _str);
}

void SetColor(int _Color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO Info;

	Info.dwSize = 1;
	Info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}