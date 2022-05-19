// Framework v 0.3
// 플레이어 몬스터 씬관리 투사체 충돌

// Bullet이 몬스터와 충돌 시 Bullet 제거
#include "Header.h"

int main(void)
{

	HideCursor(false); // 커서를 숨김

	// 배경 초기화
	
	DrawTextInfo BackGround[30];


	for (int i = 0; i < 30; ++i)
	{
		// 랜덤값을 초기화 해줌, 큰 값이 나올 수 있도록 time값끼리 곱해줄 것이지만
		// for문이 빠르게 돌게되면 time의 증가값보다 빠를 수 있기 때문에
		// 랜덤값이라고 하더라도 연속으로 같은 값이 나올 수 있음
		// i의 값을 곱하고 더해줌으로써 중복값이 나오지 않도록 해줌
		srand((GetTickCount() + i * i)* GetTickCount());


		// 현재 어떻게 사용할지 정하지 않았지만, 추후 배경과 총알을 구분지어 플레이어가 배경과 닿았을때
		// 총알에 닿았을 때에만 충돌판정이 되도록 설정해줄 것임
		BackGround[i].Info.Option = 0;

		// 좌표를 랜덤으로 설정
		BackGround[i].TransInfo.Position.x = rand() % 100 + 10;
		BackGround[i].TransInfo.Position.y = rand() % 26 + 1;

		BackGround[i].Info.Texture = (char*)"*";

		BackGround[i].Info.Color = rand() % 8 + 1;

	}

	// ** 플레이어 선언 및 동적할당
	Object* Player = new Object;

	// ** 플레이어 초기화
	Initialize(Player, (char*)"옷/", 30, 10);

	Object* Enemy = new Object;
	Initialize(Enemy, (char*)"홋", 80, 10);

	// 현재 시간으로 초기화
	ULONGLONG Time = GetTickCount64();

	int Score = 0;

	Object* Bullet[128] = { nullptr };

	int BulletCount = 0;
	// 출력
	while (true)
	{
		// 초기화된 시간부터 +50만큼 증가하면
		// 프레임과 프레임 사이의 시간 간격을 0.5초로 세팅
		if (Time + 80 < GetTickCount64())
		{
			// 증가된 값만큼 다시 초기화
			Time = GetTickCount64();

			system("cls");

			// ** 배경 출력
			for (int i = 0; i < 30; ++i)
			{
				OnDrawText(
					BackGround[i].Info.Texture,
					BackGround[i].TransInfo.Position.x,
					BackGround[i].TransInfo.Position.y,
					BackGround[i].Info.Color);

				// ** 배경으로 사용될 텍스처의 색상을 랜덤으로 설정.
				BackGround[i].Info.Color = rand() % 8 + 1;
			}

			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i] != nullptr)
				{
					if (Bullet[i]->TransInfo.Position.x + Bullet[i]->TransInfo.Scale.x >= 120)
					{
						delete Bullet[i];
						Bullet[i] = nullptr;	// 반복문 안에서 delete는 위험

						--BulletCount;
					}
				}
			}
			
			Collision(Player, Enemy);
		
			// 상 키를 입력받음
			if (GetAsyncKeyState(VK_UP))
			{
				Player->TransInfo.Position.y -= 1;
			}

			// 하 키를 입력받음
			if (GetAsyncKeyState(VK_DOWN))
			{
				Player->TransInfo.Position.y += 1;
			}

			// 좌 키를 입력받음
			if (GetAsyncKeyState(VK_LEFT))
			{
				Player->TransInfo.Position.x -= 1;
			}

			// 우 키를 입력받음
			if (GetAsyncKeyState(VK_RIGHT))
			{
				Player->TransInfo.Position.x += 1;
			}

			// 스페이스 키를 입력받음
			if (GetAsyncKeyState(VK_SPACE))
			{
				for (int i = 0; i < 128; ++i)
				{
					if(Bullet[i] == nullptr)
						Bullet[i] = CreateBullet(
							Player->TransInfo.Position.x,
							Player->TransInfo.Position.y);
					++BulletCount;
					break;
				}
			}

			OnDrawText(Enemy->Info.Texture,
				Enemy->TransInfo.Position.x,
				Enemy->TransInfo.Position.y,
				12);

			OnDrawText(Player->Info.Texture,
				Player->TransInfo.Position.x,
				Player->TransInfo.Position.y,
				10);

			// Bullet 출력
			for (int i = 0; i < 128; ++i)
			{
				if (Bullet[i])
				{
					Bullet[i]->TransInfo.Position.x += 2;
					OnDrawText(Bullet[i]->Info.Texture,
						Bullet[i]->TransInfo.Position.x,
						Bullet[i]->TransInfo.Position.y);
				}
			}

			
			OnDrawText((char*)"Bullet Count : ", 95, 1);
			OnDrawText(BulletCount, 95 + strlen("Bullet Count : "), 1);

			OnDrawText((char*)"Score : ", 60 - strlen("Score : "), 1);
			OnDrawText(++Score, 60, 1);


		}
	}

	return 0;
}
