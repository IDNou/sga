#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	ifstream jsoninfo;
	jsoninfo.open("LevelInfo.json");
	jsoninfo >> LevelInfo;
	jsoninfo.close();

	PlayerImage = g_pImageManager->FindImage("PlayerMoveAction");
	CommunicationBox = g_pImageManager->FindImage("CommunicationBox");
	MoveCount = 0;
	BuyCount = 1;
	ItemATK = 0;
	ItemDEF = 0;
	DivainCount = 100;
	AlphaValue = 255;

	LProveX = PosX + PlayerImage->GetFrameWidth() / 2 - PlayerSize/3;
	RProveX = PosX + PlayerImage->GetFrameWidth() / 2 + PlayerSize/3;
	TProveX = PosX + PlayerImage->GetFrameWidth() / 2;
	BProveX = PosX + PlayerImage->GetFrameWidth() / 2;
									
	LProveY = PosY + PlayerImage->GetFrameHeight() / 2 +10;
	RProveY = PosY + PlayerImage->GetFrameHeight() / 2 +10;
	TProveY = PosY + PlayerImage->GetFrameHeight() / 2 +5;
	BProveY = PosY + PlayerImage->GetFrameHeight() / 2 + PlayerSize/2 +5;

	isLeft = false;
	isRight = false;
	isUp = false;
	isDown = false;
	isAttack = false;
	isBuy = false;
	isLevelUp = false;
	Direction = DOWN;
	isHit = false;
	isDivain = false;
	AlphaPlag = false;
}

void cPlayer::Update()
{
	if (isHit)
	{
		switch (Direction)
		{
		case 0:
			if (!g_pPixelManager->CheckPixel(Terrain, LProveX, LProveY))
				PosX -= 1;
			break;
		case 1:
			if (!g_pPixelManager->CheckPixel(Terrain, RProveX, RProveY))
				PosX += 1;
			break;
		case 2:
			if (!g_pPixelManager->CheckPixel(Terrain, TProveX, TProveY))
				PosY -= 1;
			break;
		case 3:
			if (!g_pPixelManager->CheckPixel(Terrain, BProveX, BProveY))
				PosY += 1;
			break;
		}
	}

	if (!isAttack && !isDivain)
	{
		//Left
		if (g_pKeyManager->isOnceKeyDown(VK_LEFT) && !g_pPixelManager->CheckPixel(Terrain, LProveX, LProveY))
		{
			MoveCount = MOVECOUNT;
			PlayerImage->SetFrameY(0);
			PlayerImage->SetFrameX(1);
			isLeft = true;
			Direction = LEFT;
		}
		else if (g_pKeyManager->isStayKeyDown(VK_LEFT) && !g_pPixelManager->CheckPixel(Terrain, LProveX, LProveY))
		{
			if (PosX > 0)
			{
				//PlayerImage->SetPosX(PlayerImage->GetPosX() - MoveSpeed);
				PosX -= 2;
			}

			LProveX = PosX + PlayerImage->GetFrameWidth() / 2 - PlayerSize / 3;
			RProveX = PosX + PlayerImage->GetFrameWidth() / 2 + PlayerSize / 3;
			TProveX = PosX + PlayerImage->GetFrameWidth() / 2;
			BProveX = PosX + PlayerImage->GetFrameWidth() / 2;

			if (MoveCount < 0)
			{
				MoveCount = MOVECOUNT;
				PlayerImage->SetFrameX(PlayerImage->GetFrameX() + 1);
				if (PlayerImage->GetFrameX() > PlayerImage->GetMaxFrameX())
				{
					PlayerImage->SetFrameX(1);
				}
			}

			MoveCount--;
		}


		//Right
		if (g_pKeyManager->isOnceKeyDown(VK_RIGHT) && !g_pPixelManager->CheckPixel(Terrain, RProveX, RProveY))
		{
			MoveCount = MOVECOUNT;
			PlayerImage->SetFrameY(1);
			PlayerImage->SetFrameX(1);
			isRight = true;
			Direction = RIGHT;
		}
		else if (g_pKeyManager->isStayKeyDown(VK_RIGHT) && !g_pPixelManager->CheckPixel(Terrain, RProveX, RProveY))
		{
			if (PosX + PlayerImage->GetFrameWidth() < Terrain->GetWidth())
			{
				//PlayerImage->SetPosX(PlayerImage->GetPosX() + MoveSpeed);
				PosX += 2;
			}

			LProveX = PosX + PlayerImage->GetFrameWidth() / 2 - PlayerSize / 3;
			RProveX = PosX + PlayerImage->GetFrameWidth() / 2 + PlayerSize / 3;
			TProveX = PosX + PlayerImage->GetFrameWidth() / 2;
			BProveX = PosX + PlayerImage->GetFrameWidth() / 2;

			if (MoveCount < 0)
			{
				MoveCount = MOVECOUNT;
				PlayerImage->SetFrameX(PlayerImage->GetFrameX() + 1);
				if (PlayerImage->GetFrameX() > PlayerImage->GetMaxFrameX())
				{
					PlayerImage->SetFrameX(1);
				}
			}

			MoveCount--;
		}



		//Up
		if (g_pKeyManager->isOnceKeyDown(VK_UP) && !g_pPixelManager->CheckPixel(Terrain, TProveX, TProveY))
		{
			MoveCount = MOVECOUNT;
			PlayerImage->SetFrameY(2);
			PlayerImage->SetFrameX(1);
			isUp = true;
			Direction = UP;
		}
		else if (g_pKeyManager->isStayKeyDown(VK_UP) && !g_pPixelManager->CheckPixel(Terrain, TProveX, TProveY))
		{
			if (PosY > 0)
			{
			//	PlayerImage->SetPosY(PlayerImage->GetPosY() - MoveSpeed);
				PosY -= 2;
			}

			LProveY = PosY + PlayerImage->GetFrameHeight() / 2 + 10;
			RProveY = PosY + PlayerImage->GetFrameHeight() / 2 + 10;
 			TProveY = PosY + PlayerImage->GetFrameHeight() / 2 + 5;
			BProveY = PosY + PlayerImage->GetFrameHeight() / 2 + PlayerSize / 2 + 5;

			if (MoveCount < 0)
			{
				MoveCount = MOVECOUNT;
				PlayerImage->SetFrameX(PlayerImage->GetFrameX() + 1);
				if (PlayerImage->GetFrameX() > PlayerImage->GetMaxFrameX())
				{
					PlayerImage->SetFrameX(1);
				}
			}

			MoveCount--;
		}



		//Down
		if (g_pKeyManager->isOnceKeyDown(VK_DOWN) && !g_pPixelManager->CheckPixel(Terrain, BProveX, BProveY))
		{
			MoveCount = MOVECOUNT;
			PlayerImage->SetFrameY(3);
			PlayerImage->SetFrameX(1);
			isDown = true;
			Direction = DOWN;
		}
		else if (g_pKeyManager->isStayKeyDown(VK_DOWN) && !g_pPixelManager->CheckPixel(Terrain, BProveX, BProveY))
		{
			if (PosY + PlayerImage->GetFrameHeight() < Terrain->GetHeight())
			{
			//	PlayerImage->SetPosY(PlayerImage->GetPosY() + MoveSpeed);
				PosY += 2;
			}

			LProveY = PosY + PlayerImage->GetFrameHeight() / 2 + 10;
			RProveY = PosY + PlayerImage->GetFrameHeight() / 2 + 10;
			TProveY = PosY + PlayerImage->GetFrameHeight() / 2 + 5;
			BProveY = PosY + PlayerImage->GetFrameHeight() / 2 + PlayerSize / 2 + 5;

			if (MoveCount < 0)
			{
				MoveCount = MOVECOUNT;
				PlayerImage->SetFrameX(PlayerImage->GetFrameX() + 1);
				if (PlayerImage->GetFrameX() > PlayerImage->GetMaxFrameX())
				{
					PlayerImage->SetFrameX(1);
				}
			}

			MoveCount--;
		}


		if (g_pKeyManager->isOnceKeyUp(VK_LEFT))
		{
			PlayerImage->SetFrameX(0);
			if (isUp)
			{
				PlayerImage->SetFrameY(2);
			}
			if (isDown)
			{
				PlayerImage->SetFrameY(3);
			}
			isLeft = false;
		}
		else if (g_pKeyManager->isOnceKeyUp(VK_RIGHT))
		{
			PlayerImage->SetFrameX(0);
			if (isUp)
			{
				PlayerImage->SetFrameY(2);
			}
			if (isDown)
			{
				PlayerImage->SetFrameY(3);
			}
			isRight = false;
		}
		else if (g_pKeyManager->isOnceKeyUp(VK_UP))
		{
			PlayerImage->SetFrameX(0);
			if (isLeft)
			{
				PlayerImage->SetFrameY(0);
			}
			if (isRight)
			{
				PlayerImage->SetFrameY(1);
			}
			isUp = false;
		}
		else if (g_pKeyManager->isOnceKeyUp(VK_DOWN))
		{
			PlayerImage->SetFrameX(0);
			if (isLeft)
			{
				PlayerImage->SetFrameY(0);
			}
			if (isRight)
			{
				PlayerImage->SetFrameY(1);
			}
			isDown = false;
		}
	}
	else if (isAttack)
	{
		if (MoveCount < 0)
		{
			MoveCount = MOVECOUNT;
			PlayerImage->SetFrameX(PlayerImage->GetFrameX() + 1);
			if (PlayerImage->GetFrameX() > PlayerImage->GetMaxFrameX())
			{
				PlayerImage = g_pImageManager->FindImage("PlayerMoveAction");
				AttackRect = RectMake(0, 0, 0, 0);
				isAttack = false;
			}
		}

		MoveCount--;
	}
	else if (isDivain)
	{
		if (DivainCount < 0)
		{
			DivainCount = 200;
			isDivain = false;
			isHit = false;
		}
		DivainCount--;
	}

	//공격
	if (g_pKeyManager->isOnceKeyDown(VK_SPACE) && !isAttack && !isDivain)
	{
		isLevelUp = false;
		if (Terrain == g_pImageManager->FindImage("House_Magenta"))
		{
			isBuy = true;
		}
		else {
			PlayerImage = g_pImageManager->FindImage("PlayerAttackAction");
			PlayerImage->SetPosX(PosX);
			PlayerImage->SetPosY(PosY);
			MoveCount = MOVECOUNT;

			switch (Direction)
			{
			case LEFT:
				PlayerImage->SetFrameY(3);
				PlayerImage->SetFrameX(0);
				AttackRect = RectMakeCenter(LProveX, LProveY, PlayerImage->GetFrameWidth(), PlayerImage->GetFrameHeight());
				//공격 렉트 생성
				break;
			case RIGHT:
				PlayerImage->SetFrameY(1);
				PlayerImage->SetFrameX(0);
				AttackRect = RectMakeCenter(RProveX, RProveY, PlayerImage->GetFrameWidth(), PlayerImage->GetFrameHeight());
				break;
			case UP:
				PlayerImage->SetFrameY(0);
				PlayerImage->SetFrameX(0);
				AttackRect = RectMakeCenter(TProveX, TProveY, PlayerImage->GetFrameWidth(), PlayerImage->GetFrameHeight());
				break;
			case DOWN:
				PlayerImage->SetFrameY(2);
				PlayerImage->SetFrameX(0);
				AttackRect = RectMakeCenter(BProveX, BProveY, PlayerImage->GetFrameWidth(), PlayerImage->GetFrameHeight());
				break;
			default:
				break;
			}

			isAttack = true;
		}
	}

	//레벨업
	if (LV < 19 && EXP >= MAXEXP)
	{
		isLevelUp = true;
		LV++;
		EXP = EXP - MAXEXP;
		HP = LevelInfo["Level"][LV - 1]["HP"];
		MAXHP = LevelInfo["Level"][LV - 1]["MAXHP"];
		ATK = LevelInfo["Level"][LV - 1]["ATK"];
		DEF = LevelInfo["Level"][LV - 1]["DEF"];
		MAXEXP = LevelInfo["Level"][LV - 1]["MAXEXP"];
	}

	//인벤토리
	if (g_pKeyManager->isOnceKeyDown('I'))
	{
		HP -= 5;
		MONEY += 50;
	}

	//아이템 삭제
	if (g_pKeyManager->isOnceKeyDown('G'))
	{
		for (auto iter = PlayerInven.begin(); iter != PlayerInven.end(); )
		{
			if ((*iter)->GetName() == "ManaSword")
				iter = PlayerInven.erase(iter);
			else
				iter++;
		}
		g_pItemManager->ItemRelease("ManaSword");
	}

}

void cPlayer::Render(HDC hdc)
{
	char buffer[255];

	RectangleMake(hdc, AttackRect);
	if(!isDivain)
		PlayerImage->FrameRender(hdc, PosX, PosY, PlayerImage->GetFrameX(), PlayerImage->GetFrameY(), PlayerImage->GetFrameWidth(), PlayerImage->GetFrameHeight());
	else
	{
		PlayerImage->AlphaRender(hdc, PosX, PosY, PlayerImage->GetFrameX(), PlayerImage->GetFrameY(), AlphaValue);

		if (AlphaValue < 65)
			AlphaPlag = true;
		else if (AlphaValue > 250)
			AlphaPlag = false;

		if (!AlphaPlag)
			AlphaValue -= 10;
		else
			AlphaValue += 10;
	}
	RectangleMakeCenter(hdc, PosX + PlayerImage->GetFrameWidth() / 2, PosY + PlayerImage->GetFrameHeight()/2 +10, 10, 10);
	RectangleMakeCenter(hdc, LProveX, LProveY, 5, 5);
	RectangleMakeCenter(hdc, RProveX, RProveY, 5, 5);
	RectangleMakeCenter(hdc, TProveX, TProveY, 5, 5);
	RectangleMakeCenter(hdc, BProveX, BProveY, 5, 5);

	if (isLevelUp)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (i == 0 && j == 0)
					CommunicationBox->FrameRender(hdc, ViewPort.left + 140 + j * 15, ViewPort.top + 20 + i * 15, 0, 0);
				else if (i == 0 && j == 20 - 1)
					CommunicationBox->FrameRender(hdc, ViewPort.left + 140 + j * 15, ViewPort.top + 20 + i * 15, 2, 0);
				else if (i == 3 - 1 && j == 0)													  
					CommunicationBox->FrameRender(hdc, ViewPort.left + 140 + j * 15, ViewPort.top + 20 + i * 15, 0, 2);
				else if (i == 3 - 1 && j == 20 - 1)
					CommunicationBox->FrameRender(hdc, ViewPort.left + 140 + j * 15, ViewPort.top + 20 + i * 15, 2, 2);
				else if (i == 0 && (j != 0 || j != 20 - 1))
					CommunicationBox->FrameRender(hdc, ViewPort.left + 140 + j * 15, ViewPort.top + 20 + i * 15, 1, 0);
				else if ((i != 0 || i != 3 - 1) && j == 0)									 
					CommunicationBox->FrameRender(hdc, ViewPort.left + 140 + j * 15, ViewPort.top + 20 + i * 15, 0, 1);
				else if ((i != 0 || i != 3 - 1) && j == 20 - 1)
					CommunicationBox->FrameRender(hdc, ViewPort.left + 140 + j * 15, ViewPort.top + 20 + i * 15, 2, 1);
				else if (i == 3 - 1 && (j != 0 || j != 20 - 1))
					CommunicationBox->FrameRender(hdc, ViewPort.left + 140 + j * 15, ViewPort.top + 20 + i * 15, 1, 2);
			}
		}

		sprintf_s(buffer, "레벨업 하셨습니다. LV%d -> LV%d", LV - 1, LV);
		SetBkMode(hdc, TRANSPARENT);
		//SetTextColor(hdc, RGB(255, 255, 255));
		
		HFONT myFont = CreateFont(18, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "궁서체");
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
		TextOut(hdc, ViewPort.left + 150, ViewPort.top + 30, buffer, strlen(buffer));
		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}
}