#include "stdafx.h"
#include "cTestPlayer.h"
#include "cItemKind.h"


cTestPlayer::cTestPlayer()
{
}


cTestPlayer::~cTestPlayer()
{
}

void cTestPlayer::Setup()
{
	kind = new cItemKind;
	kind->Setup();

	PosX = WINSIZEX / 2;
	PosY = WINSIZEY / 2;
	PlayerImage = g_pImageManager->FindImage("Player");
	HP = 100;
	MP = 100;
	ATK = 10;
	DEF = 10;
	STR = 5;
	INT = 5;
	AGL = 5;
	Money = 0;
	isDie = false;

	count = MoveCount;
	Incount = MoveCount;
	Lock = false;
}

void cTestPlayer::Update()
{
	kind->Update();

	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		PlayerImage->SetFrameY(3);
		if (count < 0)
		{
			count = MoveCount;
			PlayerImage->SetFrameX(PlayerImage->GetFrameX() + 1);
			PosY -= MoveSpeed;
		}

		if (PlayerImage->GetFrameX() > PlayerImage->GetMaxFrameX())
		{
			PlayerImage->SetFrameX(0);
		}

		count--;
	}
	else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		PlayerImage->SetFrameY(0);
		if (count < 0)
		{
			count = MoveCount;
			PlayerImage->SetFrameX(PlayerImage->GetFrameX() + 1);
			PosY += MoveSpeed;
		}

		if (PlayerImage->GetFrameX() > PlayerImage->GetMaxFrameX())
		{
			PlayerImage->SetFrameX(0);
		}

		count--;
	}
	else if (g_pKeyManager->isStayKeyDown(VK_LEFT) && !Lock)
	{
		PlayerImage->SetFrameY(1);
		if (count < 0)
		{
			count = MoveCount;
			Lock = true;
			while (1)
			{
				if (Incount < 0)
				{
					Incount = MoveCount;
					PlayerImage->SetFrameX(PlayerImage->GetFrameX() + 1);
					PosX -= MoveSpeed;
				}

				if (PlayerImage->GetFrameX() > PlayerImage->GetMaxFrameX())
				{
					PlayerImage->SetFrameX(0);
					Lock = false;
					break;
				}

				Incount--;
			}
		}

		count--;
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		PlayerImage->SetFrameY(2);
		if (count < 0)
		{
			count = MoveCount;
			PlayerImage->SetFrameX(PlayerImage->GetFrameX() + 1);
			PosX += MoveSpeed;
		}

		if (PlayerImage->GetFrameX() > PlayerImage->GetMaxFrameX())
		{
			PlayerImage->SetFrameX(0);
		}

		count--;
	}

	if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{

	}
}

void cTestPlayer::Render()
{
	PlayerImage->FrameRender(g_hDC, PosX, PosY, PlayerImage->GetFrameX(), PlayerImage->GetFrameY());
}
