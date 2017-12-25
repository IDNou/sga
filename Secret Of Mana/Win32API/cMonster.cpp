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

	// ���� �޾����� �ڷιи��°�
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
			// �����̴°�(ȥ�ڼ� �����ϋ�)
			if (isMoveStart)
			{
				if (DirDelay < 0)
				{
					DirDelay = 10;
					switch (Direction)
					{
					case MON_LEFT:
						if (Name == "Rabit")
							SetFrameY(1);
						else if (Name == "Bee")
							SetFrameY(3);
						else if (Name == "Cobolt")
							SetFrameY(0);
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
						if (Name == "Rabit")
							SetFrameY(0);
						else if (Name == "Bee")
							SetFrameY(2);
						else if (Name == "Cobolt")
							SetFrameY(1);
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
						if (Name == "Rabit")
							SetFrameY(1);
						else if (Name == "Bee")
							SetFrameY(3);
						else if (Name == "Cobolt")
							SetFrameY(2);
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
						if (Name == "Rabit")
							SetFrameY(0);
						else if (Name == "Bee")
							SetFrameY(2);
						else if (Name == "Cobolt")
							SetFrameY(3);
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
		//��ġ ��尡 Ʈ��(�����ȿ� ���Դ�.)
		else
		{
			//��� ��ġ���ִ���
			//���� ���������� Ȯ��
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
				//�̰� ���ݸ���
				// ��⿡ ���ǹ����� �������� ���Ÿ����� �������ָ� ������.
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
						switch (Direction)
						{
						case MON_LEFT:
							SetFrameY(4);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > MonsterImage->GetMaxFrameX())
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case MON_RIGHT:
							SetFrameY(5);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > MonsterImage->GetMaxFrameX())
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case MON_UP:
							SetFrameY(4);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > MonsterImage->GetMaxFrameX())
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case MON_DOWN:
							SetFrameY(5);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > MonsterImage->GetMaxFrameX())
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
					else if (Name == "Cobolt")
					{
						switch (Direction)
						{
						case MON_LEFT:
							SetFrameY(4);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > MonsterImage->GetMaxFrameX())
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case MON_RIGHT:
							SetFrameY(5);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > MonsterImage->GetMaxFrameX())
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case MON_UP:
							SetFrameY(6);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > MonsterImage->GetMaxFrameX())
								{
									AttackDelay = 150;
									isAttacking = false;
									isShowAttackRect = true;
									SetFrameX(0);
								}
							}
							break;
						case MON_DOWN:
							SetFrameY(7);
							if (AttackCount < 0)
							{
								AttackCount = 20;
								SetFrameX(GetFrameX() + 1);
								if (GetFrameX() > MonsterImage->GetMaxFrameX())
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
				}
				
				AttackCount--;
				
			}
			else
			{
				Angle = GetAngle(PosX, PosY, Player->GetPosX(), Player->GetPosY());

				if (DirDelay < 0)
				{
					DirDelay = 10;

					if (Name == "Rabit")
					{
						//��������
						if (cosf(PI / 180 * Angle) * RabitSeachSpeed > 0 && -sinf(PI / 180 * Angle) * RabitSeachSpeed < 0)
						{
							SetFrameY(0);
							if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
								PosX += cosf(PI / 180 * Angle) * RabitSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
								PosY += -sinf(PI / 180 * Angle) * RabitSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
						// �����ʾƷ�
						else if (cosf(PI / 180 * Angle) * RabitSeachSpeed > 0 && -sinf(PI / 180 * Angle) * RabitSeachSpeed > 0)
						{
							SetFrameY(0);
							if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
								PosX += cosf(PI / 180 * Angle) * RabitSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
								PosY += -sinf(PI / 180 * Angle) * RabitSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
						//���ʾƷ�
						else if (cosf(PI / 180 * Angle) * RabitSeachSpeed < 0 && -sinf(PI / 180 * Angle) * RabitSeachSpeed > 0)
						{
							SetFrameY(1);
							if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
								PosX += cosf(PI / 180 * Angle) * RabitSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
								PosY += -sinf(PI / 180 * Angle) * RabitSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
						// ������
						else if (cosf(PI / 180 * Angle) * RabitSeachSpeed < 0 && -sinf(PI / 180 * Angle) * RabitSeachSpeed < 0)
						{
							SetFrameY(1);
							if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
								PosX += cosf(PI / 180 * Angle) * RabitSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
								PosY += -sinf(PI / 180 * Angle) * RabitSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
					}
					else if (Name == "Bee")
					{
						//��������
						if (cosf(PI / 180 * Angle) * BeeSeachSpeed > 0 && -sinf(PI / 180 * Angle) * BeeSeachSpeed < 0)
						{
							SetFrameY(3);
							if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
								PosX += cosf(PI / 180 * Angle) * BeeSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
								PosY += -sinf(PI / 180 * Angle) * BeeSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
						// �����ʾƷ�
						else if (cosf(PI / 180 * Angle) * BeeSeachSpeed > 0 && -sinf(PI / 180 * Angle) * BeeSeachSpeed > 0)
						{
								SetFrameY(3);
							if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
								PosX += cosf(PI / 180 * Angle) * BeeSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
								PosY += -sinf(PI / 180 * Angle) * BeeSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
						//���ʾƷ�
						else if (cosf(PI / 180 * Angle) * BeeSeachSpeed < 0 && -sinf(PI / 180 * Angle) * BeeSeachSpeed > 0)
						{
								SetFrameY(2);
							if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
								PosX += cosf(PI / 180 * Angle) * BeeSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
								PosY += -sinf(PI / 180 * Angle) * BeeSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
						// ������
						else if (cosf(PI / 180 * Angle) * BeeSeachSpeed < 0 && -sinf(PI / 180 * Angle) * BeeSeachSpeed < 0)
						{
								SetFrameY(2);
							if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
								PosX += cosf(PI / 180 * Angle) * BeeSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
								PosY += -sinf(PI / 180 * Angle) * BeeSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
					}
					else if (Name == "Cobolt")
					{
						//��������
						if (cosf(PI / 180 * Angle) * CoboltSeachSpeed > 0 && -sinf(PI / 180 * Angle) * CoboltSeachSpeed < 0)
						{
							SetFrameY(1);
							if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
								PosX += cosf(PI / 180 * Angle) * CoboltSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
								PosY += -sinf(PI / 180 * Angle) * CoboltSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
						// �����ʾƷ�
						else if (cosf(PI / 180 * Angle) * CoboltSeachSpeed > 0 && -sinf(PI / 180 * Angle) * CoboltSeachSpeed > 0)
						{
							SetFrameY(1);
							if (!g_pPixelManager->CheckPixel(Terrain, RProve.x, RProve.y))
								PosX += cosf(PI / 180 * Angle) * CoboltSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
								PosY += -sinf(PI / 180 * Angle) * CoboltSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
						//���ʾƷ�
						else if (cosf(PI / 180 * Angle) * CoboltSeachSpeed < 0 && -sinf(PI / 180 * Angle) * CoboltSeachSpeed > 0)
						{
							SetFrameY(0);
							if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
								PosX += cosf(PI / 180 * Angle) * CoboltSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, BProve.x, BProve.y))
								PosY += -sinf(PI / 180 * Angle) * CoboltSeachSpeed;
							SetFrameX(GetFrameX() + 1);
							if (GetFrameX() > MonsterImage->GetMaxFrameX())
							{
								SetFrameX(0);
							}
						}
						// ������
						else if (cosf(PI / 180 * Angle) * CoboltSeachSpeed < 0 && -sinf(PI / 180 * Angle) * CoboltSeachSpeed < 0)
						{
							SetFrameY(0);
							if (!g_pPixelManager->CheckPixel(Terrain, LProve.x, LProve.y))
								PosX += cosf(PI / 180 * Angle) * CoboltSeachSpeed;
							if (!g_pPixelManager->CheckPixel(Terrain, TProve.x, TProve.y))
								PosY += -sinf(PI / 180 * Angle) * CoboltSeachSpeed;
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
	/*HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
	RectangleMake(hdc, SeachRect);
	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);*/

	//RectangleMakeCenter(hdc,PosX + MonsterImage->GetFrameWidth()/2, PosY + MonsterImage->GetFrameHeight()/2, 90, 90);

	/*RectangleMakeCenter(hdc, LProve.x, LProve.y, 15, 30);
	RectangleMakeCenter(hdc, RProve.x, RProve.y, 15, 30);
	RectangleMakeCenter(hdc, TProve.x , TProve.y, 30, 15);
	RectangleMakeCenter(hdc, BProve.x , BProve.y, 30, 15);

	RectangleMakeCenter(hdc, LProve.x - 40, LProve.y, 15, 90);
	RectangleMakeCenter(hdc, RProve.x + 40, RProve.y, 15, 90);
	RectangleMakeCenter(hdc, TProve.x, TProve.y - 40, 90, 15);
	RectangleMakeCenter(hdc, BProve.x, BProve.y + 40, 90, 15);*/

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
	/*RectangleMakeCenter(hdc, LProve.x, LProve.y, 5, 5);
	RectangleMakeCenter(hdc, RProve.x, RProve.y, 5, 5);
	RectangleMakeCenter(hdc, TProve.x, TProve.y, 5, 5);
	RectangleMakeCenter(hdc, BProve.x, BProve.y, 5, 5);*/

}
