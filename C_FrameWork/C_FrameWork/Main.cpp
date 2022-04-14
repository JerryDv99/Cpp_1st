#define _CRT_SECURE_NO_WARNINGS	// scanf 경고문구 무시
#include <stdio.h>
#include <string>				// 문자열
#include <time.h>				// 난수 생성
#include <malloc.h>				// 동적할당
#include <Windows.h>			// 딜레이

const int PLAYER	= 0;		// 개발 편의를 위한 상수화
const int ENEMY		= 1;

const int MAX		= 2;

int iChoice = 0;	// 사용자의 입력을 받아 상황을 나눌 변수

typedef struct tagInfo			// 스탯 정보를 저장할 구조체 struct tagInfo (INFO)
{
	char* Name;
	int HP;
	int MP;

	int EXP;

	float Att;
	float Def;

	int Level;

}INFO;

typedef struct tagObject		// 플레이어 / 몬스터를 구분할 OBJECT 구조체
{
	INFO Info;					// INFO 구조체의 스탯 정보를 참조할 Info 


}OBJECT;


// OBJECT 구조체 포인터 _Obj와 정수형 ObjectType 을 매개변수로 플레이어 / 에너미를 나눌 InitializeObject 함수 선언
void InitializeObject(OBJECT* _Obj, int ObjectType);

// 플레이어 이름을 입력받을 SetName() 함수를 선언
char* SetName();


int main(void)
{
	/*OBJECT* Player = (OBJECT*)malloc(sizeof(OBJECT*));
	InitializeObject(Player, TYPE_PLAYER);

	OBJECT* Enemy = (OBJECT*)malloc(sizeof(OBJECT*));
	InitializeObject(Enemy, TYPE_ENEMY);*/

	OBJECT* Objects[MAX];	// MAX의 값(2)만큼 OBJECT* 타입의 Objects 변수 생성

	// Objects[0](PLAYER = 0으로 상수화) = (Objects[i]의 형태인 OBJECT*타입으로 형변환)동적할당함수malloc(OBJECT*의 크기만큼 할당)
	Objects[PLAYER] = (OBJECT*)malloc(sizeof(OBJECT*));	// Object[PLAYER]를 사용하기 전에 미리 공간을 할당

	// InitializeObject 함수를 사용해 (OBJECT 구조체를 참조해 PLAYER의 스탯을 생성할 OBJECT 포인터 Object[PLAYER](0),int 0을 받아 case PLAYER)
	// 의 값을 지니는 OBJECT* 타입 변수 생성
	InitializeObject(Objects[PLAYER],PLAYER); 

	Objects[ENEMY] = (OBJECT*)malloc(sizeof(OBJECT*));	// Object[1]
	InitializeObject(Objects[ENEMY], ENEMY); 
	
	int iLoopC = 1;				// 게임 종료를 선택하기 전까지 반복
	while (iLoopC)
	{
		int iLoopCheck = 1;		// 전투 반복문을 위한 변수 초기화
		while (iLoopCheck)		// 탈출 전까지 루프	
		{ 
			// 콘솔 창을 모두 지움
			//system("cls");

			printf_s("\n[%s]\n", Objects[PLAYER]->Info.Name);
			printf_s("HP : %d\n", Objects[PLAYER]->Info.HP);
			printf_s("MP : %d\n", Objects[PLAYER]->Info.MP);
			printf_s("공격력 : %.2f\n", Objects[PLAYER]->Info.Att);
			printf_s("방어력 : %.2f\n", Objects[PLAYER]->Info.Def);
			printf_s("EXP : %d\n", Objects[PLAYER]->Info.EXP);
			printf_s("Level : %d\n\n", Objects[PLAYER]->Info.Level);

			printf_s("\n[%s]\n", Objects[ENEMY]->Info.Name);
			printf_s("HP : %d\n", Objects[ENEMY]->Info.HP);
			printf_s("MP : %d\n", Objects[ENEMY]->Info.MP);
			printf_s("공격력 : %.2f\n", Objects[ENEMY]->Info.Att);
			printf_s("방어력 : %.2f\n", Objects[ENEMY]->Info.Def);
			printf_s("EXP : %d\n", Objects[ENEMY]->Info.EXP);
			printf_s("Level : %d\n\n", Objects[ENEMY]->Info.Level);
			Sleep(100);			// Windows.h에 포함된 딜레이 함수 Sleep(1000) = 1Sec 
		
		
			printf_s("몬스터와 만났습니다. 공격하시겠습니까 ?\n1. 공격\n2. 도망\n입력 : ");
			scanf_s("%d", &iChoice);

			switch (iChoice)	
			{
			case 1:				// iChoice가 1인 경우
				printf_s("플레이어의 공격\n");
				Sleep(500);		

				// 플레이어의 공격력이 몬스터의 방어력보다 높은 경우 그 차이만큼 적의 HP 감소
				if ((Objects[PLAYER]->Info.Att > Objects[ENEMY]->Info.Def))		
					Objects[ENEMY]->Info.HP -= Objects[PLAYER]->Info.Att - Objects[ENEMY]->Info.Def;
				else
					Objects[ENEMY]->Info.HP -= 1;	// 적을 경우 최소데미지 1만큼 적의 HP 감소
				printf_s("몬스터의 공격\n");
				Sleep(500);

				// 몬스터의 공격력이 플레이어의 방어력보다 높은 경우 그 차이만큼 플레이어의 HP 감소
				if ((Objects[ENEMY]->Info.Att > Objects[PLAYER]->Info.Def))
					Objects[PLAYER]->Info.HP -= Objects[ENEMY]->Info.Att - Objects[PLAYER]->Info.Def;
				else
					Objects[PLAYER]->Info.HP -= 1;
				break;

			case 2:
				srand(time(NULL));					// time.h 포함 난수생성 함수 초기화
				if (rand() % 3 == 0)				// 생성된 난수 / 3의 나머지가 0인 경우, 1/3 확률로 탈출 실패
				{
					printf_s("도망치는것에 [실패] 했습니다. 전투를 시작합니다\n");
					Sleep(500);
					iChoice = 1;					// case 1의 전투 실행
				}
				/*else if (Objects[ENEMY]->Info.Level - Objects[PLAYER]->Info.Level >= 5)
				{
					printf_s("도망치는것에 [실패] 했습니다. 전투를 시작합니다\n");
					iChoice = 1;
				}*/
				else
				{
					printf_s("도망치는것에 [성공] 했습니다.\n");
					iLoopCheck = 0;					// 도망 성공시 전투 루프 탈출
					break;
				}
			
				Sleep(1000);
				break;

			}

			if (iLoopCheck == 0)	// 도망에 성공하면 루프 종료
				iLoopCheck = 0;
			else if (Objects[ENEMY]->Info.HP > 0 && Objects[PLAYER]->Info.HP > 0)
				iLoopCheck = 1;		// 도망에 성공하거나 한쪽의 HP가 0이 될때까지 루프
			else
				iLoopCheck = 0;		// 전투를 선택하거나 도망에 실패하고 한쪽의 HP가 0보다 낮거나 같으면 탈출

		}




		if (Objects[ENEMY]->Info.HP <= 0)		// 몬스터의 HP가 0과 같거나 적음, 적 처치
		{
			printf_s("몬스터를 처치했습니다 !\n");
			printf_s("경험치 %d 상승\n", Objects[ENEMY]->Info.EXP);
			Objects[PLAYER]->Info.EXP += Objects[ENEMY]->Info.EXP;		// 플레이어 경험치에 몬스터의 경험치 합산
			if (Objects[PLAYER]->Info.EXP >= 100)						// 경험치가 100 이상일 경우 레벨 업
			{
				printf_s("플레이어 레벨업 ! 현재 레벨 : %d Lv\n", Objects[PLAYER]->Info.Level);
				Objects[PLAYER]->Info.EXP = 0;							// 경험치 초기화
				Objects[PLAYER]->Info.Level += 1;						// 플레이어 레벨과 스탯 증가
				Objects[PLAYER]->Info.Att += 3;
				Objects[PLAYER]->Info.Att += 1;
			}

		}
		else if (Objects[PLAYER]->Info.HP <= 0)	// 플레이어 HP가 0과 같거나 적음, 전투 패배
		{
			printf_s("전투에서 패배하였습니다...\n");
			printf_s("경험치를 %d 만큼 잃었습니다\n", Objects[ENEMY]->Info.EXP);
			Objects[PLAYER]->Info.EXP -= Objects[ENEMY]->Info.EXP;
		}
		//iChoice = 0;
		printf_s("다시 시작하시겠습니까?  1. 다시 시작 2. 게임 종료\n");
		scanf_s("%d", &iChoice);
		switch (iChoice)
		{
		case 1:
			printf_s("다시 시작하셨습니다. 게임에 입장합니다\n");	// 게임 루프 반복
			Sleep(500);
			break;
		case 2:
			iLoopC = 0;											// 게임 루프 탈출
			break;
		}

	}
	Sleep(250);
	printf_s("게임을 종료합니다. 수고하셨습니다\n");





	return 0;
}

void InitializeObject(OBJECT* _Obj, int ObjectType)		// OBJECT 구조체 포인터 타입 변수와 int 변수를 매개변수로 사용하는 함수 정의부
{
	switch (ObjectType)
	{
	case PLAYER:										// 전달받은 ObjectType 값이 0인 경우 (플레이어)
		_Obj->Info.Name = SetName();					// SetName 함수 실행

		_Obj->Info.Att = 10;							// 플레이어 스탯 생성 (main에서 만든 Objects[PLAYER])
		_Obj->Info.Def = 10;
		_Obj->Info.EXP = 0;
		_Obj->Info.HP = 100;
		_Obj->Info.MP = 10;
		_Obj->Info.Level = 1;
		break;
	case ENEMY:											// 1인 경우 (몬스터)

		_Obj->Info.Name = (char*)"Enemy";

		_Obj->Info.Att = 5;
		_Obj->Info.Def = 5;
		_Obj->Info.EXP = 20;
		_Obj->Info.HP = 30;
		_Obj->Info.MP = 5;
		_Obj->Info.Level = 1;
		break;
	}

	
}


char* SetName()											// 플레이어의 이름을 입력받고 char* 타입으로 반환할 함수
{
	char Buffer[128] = "";								// 한글을 입력받기 위해 128byte 사이즈의 문자열 생성과 초기화
	
	printf_s("이름 입력 : ");
	scanf("%s", Buffer);								// 입력받은 %s값을 Buffer 문자열에 저장

	char* pName = (char*)malloc(strlen(Buffer + 1));	// 문자열 포인터를 사용하기 위한 동적 할당
	strcpy(pName, Buffer);								// Buffer 문자열에 든 값을 pName 문자열 포인터에 복사

	return pName;										// char* 타입 pName 반환
}


