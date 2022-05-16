#define _CRT_SECURE_NO_WARNINGS
#include <iostream>  // 입출력 헤더

using namespace std;	// iostream과 세트

typedef struct tagInfo
{
	int iNumber;


	tagInfo()	// 생성자, 구조체 안에서만 사용 가능
	{
		cout << "기본 생성자" << endl;	// 초기화 시 생성자 호출
	};

	tagInfo(int _iNumber)	
	{
		iNumber = _iNumber;
		cout << "복사 생성자" << endl;	// 초기화 시 생성자 호출
	};


}INFO;

int main(void)
{
	// ** 출력
	//printf_s("문자 출력");
	//cout << "문자 출력";		// console out <<(시프트 연산자) "문자열"		
	
	//꺾쇠 방향으로  << 보내기, >> 받기


	// ** 줄바꿈
	//printf_s("\\n을 사용하면 \n줄바꿈");
	//cout << "endl 을 사용하면" << endl << "줄바꿈";


	/*
	// ** 입력
	int iNumber = 0;

	
	printf_s("입력: ");
	scanf("%d", &iNumber);

	printf_s("출력 : %d", iNumber);

	cout << "입력: ";
	cin >> iNumber;

	cout << "출력 : " << iNumber;
	*/

	// ** 동적할당 
	//INFO* pInfo = (INFO*)malloc(sizeof(INFO));		// malloc의 형태가 void* 이기 때문에 형변환
	//INFO* pInfo = new INFO;	// new는 동적할당, new 뒤의 INFO는 size 및 형태
	INFO* pInfo = new INFO(10);
	cout << pInfo->iNumber << endl;


	//free(pInfo);
	delete pInfo;



	return 0;
}