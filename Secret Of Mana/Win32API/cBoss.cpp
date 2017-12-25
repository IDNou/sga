#include "stdafx.h"
#include "cBoss.h"


cBoss::cBoss()
{
}


cBoss::~cBoss()
{
}

void cBoss::Setup()
{
	BossList;
	ifstream json_List;
	json_List.open("MonsterList.json");
	json_List >> BossList;
	json_List.close();

	Player = g_pPlayerManager->GetPlayer();

	BossImage = g_pImageManager->FindImage("Boss");
	Boss_FrameX = 0;
	Boss_FrameY = 0;
	Direction = Boss_End;
	HP = BossList["Mantice"]["HP"];
	ATK = BossList["Mantice"]["ATK"];
	DEF = BossList["Mantice"]["DEF"];
	EXP = BossList["Mantice"]["EXP"];
	MONEY = GetRandom(BossList["Mantice"]["MINMONEY"], BossList["Mantice"]["MAXMONEY"]);

	AlphaValue = 255;
	MoveDelay = 100;
	DirDelay = 10;
	AttackDelay = 0;
	AttackCount = 20;
	Angle = 0;

	isShowAttackRect = false;
	isAttacking = false;
	isAttackMode = false;
	isSeachMode = false;
	isMoveStart = false;
	isHit = false;
	isDivain = false;
	AlphaPlag = false;
}

void cBoss::Update()
{
	cout << HP << endl;
	isShowAttackRect = false;

	LProve.x = PosX + BossImage->GetFrameWidth() / 2 - 20;
	RProve.x = PosX + BossImage->GetFrameWidth() / 2 + 20;
	TProve.x = PosX + BossImage->GetFrameWidth() / 2;
	BProve.x = PosX + BossImage->GetFrameWidth() / 2;

	LProve.y = PosY + BossImage->GetFrameHeight() / 2;
	RProve.y = PosY + BossImage->GetFrameHeight() / 2;
	TProve.y = PosY + BossImage->GetFrameHeight() / 2 - 20;
	BProve.y = PosY + BossImage->GetFrameHeight() / 2 + 20;

	SeachRect = RectMakeCenter(PosX + BossImage->GetFrameWidth() / 2, PosY + BossImage->GetFrameHeight() / 2, 250, 250);

	if (isHit)
	{
		switch (Direction)
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
				Direction = (TagBossDir)GetRandom(0, 3);
				isMoveStart = true;
			}
			// 움직이는거(혼자서 움직일떄)
			if (isMoveStart)
			{
				if (DirDelay < 0)
				{
					DirDelay = 10;
					SetFrameY(0);
					switch (Direction)
					{
					case Boss_Left:
						if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
							PosX -= 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > BossImage->GetMaxFrameX())
						{
							SetFrameX(0);
							isMoveStart = false;
						}
						break;
					case Boss_Right:
						if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
							PosX += 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > BossImage->GetMaxFrameX())
						{
							SetFrameX(0);
							isMoveStart = false;
						}
						break;
					case Boss_Up:
						if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
							PosY -= 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > BossImage->GetMaxFrameX())
						{
							SetFrameX(0);
							isMoveStart = false;
						}
						break;
					case Boss_Down:
						if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
							PosY += 5;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > BossImage->GetMaxFrameX())
						{
							SetFrameX(0);
							isMoveStart = false;
						}
						break;
					}
				}
			}
		}
		//써치모드가 트루일때
		else
		{
			//어디에 위치해있는지
			//공격 범위안인지 확인
			if (!isAttacking)
				isAttackMode = false;

			if (isAttackMode)
			{
				//이거 공격모드
				if (AttackDelay < 0)
				{
					SetFrameY(1);
					switch (Direction)
						{
						case Boss_Left:
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > BossImage->GetMaxFrameX())
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case Boss_Right:
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > BossImage->GetMaxFrameX())
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case Boss_Up:
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > BossImage->GetMaxFrameX())
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case Boss_Down:
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > BossImage->GetMaxFrameX())
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

				AttackCount--;

			}
			else
			{
				Angle = GetAngle(PosX, PosY, Player->GetPosX(), Player->GetPosY());

				if (DirDelay < 0)
				{
					DirDelay = 10;

					//오른쪽위
					if (cosf(PI / 180 * Angle) * RabitSeachSpeed > 0 && -sinf(PI / 180 * Angle) * RabitSeachSpeed < 0)
					{
						SetFrameY(0);
						if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
							PosX += cosf(PI / 180 * Angle) * RabitSeachSpeed;
						if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
							PosY += -sinf(PI / 180 * Angle) * RabitSeachSpeed;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > BossImage->GetMaxFrameX())
						{
							SetFrameX(0);
						}
					}
					// 오른쪽아래
					else if (cosf(PI / 180 * Angle) * RabitSeachSpeed > 0 && -sinf(PI / 180 * Angle) * RabitSeachSpeed > 0)
					{
						SetFrameY(0);
						if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
							PosX += cosf(PI / 180 * Angle) * RabitSeachSpeed;
						if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
							PosY += -sinf(PI / 180 * Angle) * RabitSeachSpeed;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > BossImage->GetMaxFrameX())
						{
							SetFrameX(0);
						}
					}
					//왼쪽아래
					else if (cosf(PI / 180 * Angle) * RabitSeachSpeed < 0 && -sinf(PI / 180 * Angle) * RabitSeachSpeed > 0)
					{
						SetFrameY(1);
						if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
							PosX += cosf(PI / 180 * Angle) * RabitSeachSpeed;
						if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
							PosY += -sinf(PI / 180 * Angle) * RabitSeachSpeed;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > BossImage->GetMaxFrameX())
						{
							SetFrameX(0);
						}
					}
					// 왼쪽위
					else if (cosf(PI / 180 * Angle) * RabitSeachSpeed < 0 && -sinf(PI / 180 * Angle) * RabitSeachSpeed < 0)
					{
						SetFrameY(1);
						if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
							PosX += cosf(PI / 180 * Angle) * RabitSeachSpeed;
						if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
							PosY += -sinf(PI / 180 * Angle) * RabitSeachSpeed;
						SetFrameX(GetFrameX() + 1);
						if (GetFrameX() > BossImage->GetMaxFrameX())
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

	MoveDelay--;
	DirDelay--;
	AttackDelay--;
}

void cBoss::Render(HDC hdc)
{
	char buffer[255];

	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	RectangleMake(hdc, SeachRect);
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	//RectangleMakeCenter(hdc, PosX+BossImage->GetFrameWidth()/2, PosY+BossImage->GetFrameHeight()/2, 40, 40);
	if (!isDivain)
	{
		BossImage->FrameRender(hdc, PosX, PosY, GetFrameX(), GetFrameY(), BossImage->GetFrameWidth(), BossImage->GetFrameHeight());
	}
	else
	{
		BossImage->AlphaRender(hdc, PosX, PosY, GetFrameX(), GetFrameY(), AlphaValue);

		if (AlphaValue < 65)
			AlphaPlag = true;
		else if (AlphaValue > 250)
			AlphaPlag = false;

		if (!AlphaPlag)
			AlphaValue -= 10;
		else
			AlphaValue += 10;

		sprintf(buffer, "%d", DamageBuffer);
		TextOut(hdc, PosX + BossImage->GetFrameWidth() / 2, PosY - 10, buffer, strlen(buffer));
	}

	/*RectangleMakeCenter(hdc, LProve.x, LProve.y, 15, 30);
	RectangleMakeCenter(hdc, RProve.x, RProve.y, 15, 30);
	RectangleMakeCenter(hdc, TProve.x, TProve.y, 30, 15);
	RectangleMakeCenter(hdc, BProve.x, BProve.y, 30, 15);

	RectangleMakeCenter(hdc, LProve.x, LProve.y, 5, 5);
	RectangleMakeCenter(hdc, RProve.x, RProve.y, 5, 5);
	RectangleMakeCenter(hdc, TProve.x, TProve.y, 5, 5);
	RectangleMakeCenter(hdc, BProve.x, BProve.y, 5, 5);*/
}
