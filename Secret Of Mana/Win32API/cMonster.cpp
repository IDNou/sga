#include "stdafx.h"
#include "cMonster.h"


cMonster::cMonster()
{
}


cMonster::~cMonster()
{
}

void cMonster::Setup()
{
	Player = g_pPlayerManager->GetPlayer();

	PosX = 0;
	PosY = 0;

	isDie = false;
	isHit = false;
	isDivain = false;

	DivainCount = 200;
	MoveDelay = 100;
	AlphaValue = 255;
	DirDelay = 10;
	AttackCount = 20;
	AttackDelay = 0;
	DamageBuffer = 0;
	Direction = MON_END;
	isMoveStart = false;
	AlphaPlag = false;
	isAttackMode = false;
	isSeachMode = false;
	isAttacking = false;
	isShowAttackRect = false;
}

void cMonster::Update()
{
	isShowAttackRect = false;

	LProve.x = PosX + MonsterImage->GetFrameWidth() / 2 - 10;
	RProve.x = PosX + MonsterImage->GetFrameWidth() / 2 + 10;
	TProve.x = PosX + MonsterImage->GetFrameWidth() / 2;
	BProve.x = PosX + MonsterImage->GetFrameWidth() / 2;

	LProve.y = PosY + MonsterImage->GetFrameHeight() / 2;
	RProve.y = PosY + MonsterImage->GetFrameHeight() / 2;
	TProve.y = PosY + MonsterImage->GetFrameHeight() / 2 - 10;
	BProve.y = PosY + MonsterImage->GetFrameHeight() / 2 + 10;

	SeachRect = RectMakeCenter(PosX + MonsterImage->GetFrameWidth() / 2, PosY + MonsterImage->GetFrameHeight() / 2, 250, 250);

	// 공격 받았을때 뒤로밀리는거
	if (isHit)
	{
		switch (PushDir)
		{
		case 0:
			if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
				PosX -= 1;
			break;
		case 1:
			if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
				PosX += 1;
			break;
		case 2:
			if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
				PosY -= 1;
			break;
		case 3:
			if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
				PosY += 1;
			break;
		}
	}

	if (!isDivain)
	{
		if (!isSeachMode)
		{
			if (MoveDelay < 0)
			{
				MoveDelay = 100;
				Direction = (MoveDir)GetRandom(0, 3);
				isMoveStart = true;
			}
			// 움직이는거(혼자서 움직일떄)
			if (isMoveStart)
			{
				if (DirDelay < 0)
				{
					DirDelay = 10;
					switch (Direction)
					{
					case MON_LEFT:
						SetFrameY(1);
						if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
							PosX -= 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > MonsterImage->GetMaxFrameX())
						{
							SetFrameX(0);
							isMoveStart = false;
						}
						break;
					case MON_RIGHT:
						SetFrameY(0);
						if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
							PosX += 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > MonsterImage->GetMaxFrameX())
						{
							SetFrameX(0);
							isMoveStart = false;
						}
						break;
					case MON_UP:
						SetFrameY(1);
						if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
							PosY -= 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > MonsterImage->GetMaxFrameX())
						{
							SetFrameX(0);
							isMoveStart = false;
						}
						break;
					case MON_DOWN:
						SetFrameY(0);
						if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
							PosY += 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > MonsterImage->GetMaxFrameX())
						{
							SetFrameX(0);
							isMoveStart = false;
						}
						break;
					}
				}
			}
		}
		//서치 모드가 트루(범위안에 들어왔다.)
		else
		{
			//어디에 위치해있는지
			//공격 범위안인지 확인
			if (!isAttacking)
				isAttackMode = false;
		

			//RECT rt;
			/*if (IntersectRect(&rt,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(LProve.x-10, LProve.y, 15, 30)) && !isAttackMode)
			{
				Direction = MON_LEFT;
				SetFrameX(0);
				isAttacking = true;
				isAttackMode = true;
			}
			else if (IntersectRect(&rt,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(RProve.x + 10, RProve.y, 15, 30)) && !isAttackMode)
			{
				Direction = MON_RIGHT;
				SetFrameX(0);
				isAttacking = true;
				isAttackMode = true;
			}
			else if (IntersectRect(&rt,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(TProve.x, TProve.y - 10, 30, 15)) && !isAttackMode)
			{
				Direction = MON_UP;
				SetFrameX(0);
				isAttacking = true;
				isAttackMode = true;
			}
			else if (IntersectRect(&rt,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(BProve.x, BProve.y + 10, 30, 15)) && !isAttackMode)
			{
				Direction = MON_DOWN;
				SetFrameX(0);
				isAttacking = true;
				isAttackMode = true;
			}*/

			if (isAttackMode)
			{
				// 요기에 조건문으로 근접인지 원거리인지 구분해주면 좋을뜻.
				if (AttackDelay < 0)
				{
					if (Name == "Rabit")
					{
						switch (Direction)
						{
						case MON_LEFT:
							SetFrameY(3);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > 3)
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case MON_RIGHT:
							SetFrameY(2);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > 3)
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case MON_UP:
							SetFrameY(3);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > 3)
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case MON_DOWN:
							SetFrameY(2);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > 3)
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						}
					}
					else if (Name == "Bee")
					{

					}
					else if (Name == "Cobolt")
					{

					}
				}
				
				AttackCount--;
				
			}
			else
			{
				Angle = GetAngle(PosX, PosY, Player->GetPosX(), Player->GetPosY());

				if (DirDelay < 0)
				{
					DirDelay = 10;

					//오른쪽위
					if (cosf(PI / 180 * Angle) * 5 > 0 && -sinf(PI / 180 * Angle) * 5 < 0)
					{
						SetFrameY(0);
						if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
							PosX += cosf(PI / 180 * Angle) * 5;
						if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
							PosY += -sinf(PI / 180 * Angle) * 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > MonsterImage->GetMaxFrameX())
						{
							SetFrameX(0);
						}
					}
					// 오른쪽아래
					else if (cosf(PI / 180 * Angle) * 5 > 0 && -sinf(PI / 180 * Angle) * 5 > 0)
					{
						SetFrameY(0);
						if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
							PosX += cosf(PI / 180 * Angle) * 5;
						if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
							PosY += -sinf(PI / 180 * Angle) * 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > MonsterImage->GetMaxFrameX())
						{
							SetFrameX(0);
						}
					}
					//왼쪽아래
					else if (cosf(PI / 180 * Angle) * 5 < 0 && -sinf(PI / 180 * Angle) * 5 > 0)
					{
						SetFrameY(1);
						if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
							PosX += cosf(PI / 180 * Angle) * 5;
						if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
							PosY += -sinf(PI / 180 * Angle) * 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > MonsterImage->GetMaxFrameX())
						{
							SetFrameX(0);
						}
					}
					// 왼쪽위
					else if (cosf(PI / 180 * Angle) * 5 < 0 && -sinf(PI / 180 * Angle) * 5 < 0)
					{
						SetFrameY(1);
						if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
							PosX += cosf(PI / 180 * Angle) * 5;
						if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
							PosY += -sinf(PI / 180 * Angle) * 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > MonsterImage->GetMaxFrameX())
						{
							SetFrameX(0);
						}
					}
				}
			}
		}
	}
	else
	{
		if (DivainCount < 0)
		{
			DivainCount = 200;
			DamageBuffer = 0;
			isDivain = false;
		}
		DivainCount--;
	}

	if (AttackDelay < 0)
		AttackDelay = 0;

	DirDelay--;
	MoveDelay--;
	AttackDelay--;
}

void cMonster::Render(HDC hdc)
{
	char buffer[255];
	//RectangleMakeCenter(hdc, PosX + MonsterImage->GetFrameWidth() / 2, PosY + MonsterImage->GetFrameHeight() / 2, 20, 20);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	RectangleMake(hdc, SeachRect);
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	RectangleMakeCenter(hdc, LProve.x - 10, LProve.y, 15, 30);
	RectangleMakeCenter(hdc, RProve.x + 10, RProve.y, 15, 30);
	RectangleMakeCenter(hdc, TProve.x , TProve.y - 10, 30, 15);
	RectangleMakeCenter(hdc, BProve.x , BProve.y + 10, 30, 15);
	if (!isDivain)
	{
		MonsterImage->FrameRender(hdc, PosX, PosY, GetFrameX(), GetFrameY(), MonsterImage->GetFrameWidth(), MonsterImage->GetFrameHeight());
	}
	else
	{
		MonsterImage->AlphaRender(hdc, PosX, PosY, GetFrameX(), GetFrameY(), AlphaValue);

		if (AlphaValue < 65)
			AlphaPlag = true;
		else if (AlphaValue > 250)
			AlphaPlag = false;

		if (!AlphaPlag)
			AlphaValue -= 10;
		else
			AlphaValue += 10;

		sprintf(buffer, "%d", DamageBuffer);
		TextOut(hdc, PosX + MonsterImage->GetFrameWidth() / 2, PosY - 10, buffer, strlen(buffer));
	}
	RectangleMakeCenter(hdc, LProve.x, LProve.y, 5, 5);
	RectangleMakeCenter(hdc, RProve.x, RProve.y, 5, 5);
	RectangleMakeCenter(hdc, TProve.x, TProve.y, 5, 5);
	RectangleMakeCenter(hdc, BProve.x, BProve.y, 5, 5);

}
