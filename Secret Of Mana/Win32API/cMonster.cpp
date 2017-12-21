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
	PosX = 0;
	PosY = 0;

	isDie = false;
	isHit = false;
	isDivain = false;

	DivainCount = 200;
	MoveDelay = 100;
	AlphaValue = 255;
	DirDelay = 10;
	Direction = MON_END;
	isMoveStart = false;
	AlpghPlag = false;
}

void cMonster::Update()
{
	LProve.x = PosX + MonsterImage->GetFrameWidth() / 2 - 10;
	RProve.x = PosX + MonsterImage->GetFrameWidth() / 2 + 10;
	TProve.x = PosX + MonsterImage->GetFrameWidth() / 2;
	BProve.x = PosX + MonsterImage->GetFrameWidth() / 2;

	LProve.y = PosY + MonsterImage->GetFrameHeight() / 2;
	RProve.y = PosY + MonsterImage->GetFrameHeight() / 2;
	TProve.y = PosY + MonsterImage->GetFrameHeight() / 2 - 10;
	BProve.y = PosY + MonsterImage->GetFrameHeight() / 2 + 10;

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
		if (MoveDelay < 0)
		{
			MoveDelay = 100;
			Direction = (MoveDir)GetRandom(0, 3);
			isMoveStart = true;
		}
		// 움직이는거
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
					if(GetFrameX() > MonsterImage->GetMaxFrameX())
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
	else
	{
		if (DivainCount < 0)
		{
			DivainCount = 200;
			isDivain = false;
		}
		DivainCount--;
	}

	DirDelay--;
	MoveDelay--;
}

void cMonster::Render(HDC hdc)
{
	//RectangleMakeCenter(hdc, PosX + MonsterImage->GetFrameWidth() / 2, PosY + MonsterImage->GetFrameHeight() / 2, 20, 20);
	if (!isDivain)
	{
		MonsterImage->FrameRender(hdc, PosX, PosY, GetFrameX(), GetFrameY(), MonsterImage->GetFrameWidth(), MonsterImage->GetFrameHeight());
	}
	else
	{
		MonsterImage->AlphaRender(hdc, PosX, PosY, GetFrameX(), GetFrameY(), AlphaValue);

		if (AlphaValue < 65)
			AlpghPlag = true;
		else if (AlphaValue > 250)
			AlpghPlag = false;

		if (!AlpghPlag)
			AlphaValue -= 10;
		else
			AlphaValue += 10;
	}
	RectangleMakeCenter(hdc, LProve.x, LProve.y, 5, 5);
	RectangleMakeCenter(hdc, RProve.x, RProve.y, 5, 5);
	RectangleMakeCenter(hdc, TProve.x, TProve.y, 5, 5);
	RectangleMakeCenter(hdc, BProve.x, BProve.y, 5, 5);

}
