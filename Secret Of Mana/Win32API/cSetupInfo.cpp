#include "stdafx.h"
#include "cSetupInfo.h"
#include "cPlayer.h"

void cSetupInfo::Setup()
{
	Player = g_pPlayerManager->GetPlayer();
	BackGround = g_pImageManager->AddImage("BackGround", "images/SetupInfoBackGround.png", 32, 32, true, RGB(255, 0, 255));
	StatMessegeBox = g_pImageManager->AddFrameImage("MessegeBox", "images/StatMessegeBox.png", 45, 45, 3, 3, true, RGB(255, 0, 255));
	Finger = g_pImageManager->AddImage("Finger", "images/Finger.png", 16, 16, true, RGB(255, 0, 255));
	Finger->SetPosX(560);
	Finger->SetPosY(150);
	boxSize = 0;
	count = 1;
	InvenWidth = 600;
	InvenHeight = 150;
	isFullHP = false;

}

void cSetupInfo::Release()
{
	g_pImageManager->ReleaseImage("BackGround");
	g_pImageManager->ReleaseImage("MessegeBox");
	g_pImageManager->ReleaseImage("Finger");
}


void cSetupInfo::Update()
{
	if (boxSize >= 32)
	{
		boxSize = 0;
	}

	if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		isFullHP = false;
		//물약류 사용
		if (Player->GetPlayerInven()[count - 1]->GetType() == (ItemType)0)
		{
			if (Player->GetHP() == Player->GetMAXHP())
			{
				isFullHP = true;
			}
			else if (Player->GetHP() < Player->GetMAXHP() && Player->GetMAXHP() > Player->GetHP() + Player->GetPlayerInven()[count - 1]->GetHP())
			{
				Player->SetHp(Player->GetHP() + Player->GetPlayerInven()[count - 1]->GetHP());
				Player->GetPlayerInven()[count - 1]->SetAmount(Player->GetPlayerInven()[count - 1]->GetAmount() - 1);
			}
			else if (Player->GetHP() < Player->GetMAXHP() && Player->GetMAXHP() <= Player->GetHP() + Player->GetPlayerInven()[count - 1]->GetHP())
			{
				Player->SetHp(Player->GetMAXHP());
				Player->GetPlayerInven()[count - 1]->SetAmount(Player->GetPlayerInven()[count - 1]->GetAmount() - 1);
			}

			if (Player->GetPlayerInven()[count - 1]->GetAmount() == 0)
			{
				for (auto iter = Player->GetPlayerInven().begin(); iter != Player->GetPlayerInven().end(); )
				{
					if ((*iter)->GetName() == Player->GetPlayerInven()[count - 1]->GetName())
					{
						iter = Player->GetPlayerInven().erase(iter);
						break;
					}
					else
						iter++;
				}
			}
		}
		// 아이템 착용
		else if (Player->GetPlayerInven()[count - 1]->GetType() == (ItemType)1 && !Player->GetPlayerInven()[count - 1]->GetIsWearSword())
		{
			Player->GetPlayerInven()[count - 1]->SetIsWearSword(true);
			Player->SetItemATK(Player->GetPlayerInven()[count - 1]->GetATK());
			//Player->SetATK(Player->GetATK() + Player->GetPlayerInven()[count - 1]->GetATK());
			//Player->SetDEF(Player->GetDEF() + Player->GetPlayerInven()[count - 1]->GetDEF());
		}
		// 아이템 해제
		else if (Player->GetPlayerInven()[count - 1]->GetType() == (ItemType)1 && Player->GetPlayerInven()[count - 1]->GetIsWearSword())
		{
			Player->GetPlayerInven()[count - 1]->SetIsWearSword(false);
			Player->SetItemATK(0);
			//Player->SetATK(Player->GetATK() - Player->GetPlayerInven()[count - 1]->GetATK());
			//Player->SetDEF(Player->GetDEF() - Player->GetPlayerInven()[count - 1]->GetDEF());
		}
		else if (Player->GetPlayerInven()[count - 1]->GetType() == (ItemType)2 && !Player->GetPlayerInven()[count - 1]->GetIsWearAmor())
		{
			Player->GetPlayerInven()[count - 1]->SetIsWearAmor(true);
			Player->SetItemDEF(Player->GetPlayerInven()[count - 1]->GetDEF());
			//Player->SetDEF(Player->GetDEF() + Player->GetPlayerInven()[count - 1]->GetDEF());
		}
		else if (Player->GetPlayerInven()[count - 1]->GetType() == (ItemType)2 && Player->GetPlayerInven()[count - 1]->GetIsWearAmor())
		{
			Player->GetPlayerInven()[count - 1]->SetIsWearAmor(false);
			Player->SetItemDEF(0);
			//Player->SetDEF(Player->GetDEF() - Player->GetPlayerInven()[count - 1]->GetDEF());
		}
	}

	if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		if (count > 1)
		{
			Finger->SetPosY(Finger->GetPosY() - 50);
			count--;
		}
	}
	if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		if (count < Player->GetPlayerInven().size())
		{
			Finger->SetPosY(Finger->GetPosY() + 50);
			count++;
		}
	}

	boxSize++;
}

void cSetupInfo::Render()
{
	char ch_buffer[255];
	InvenHeight = 150;

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 37; j++)
		{
			BackGround->Render(g_hDC, j*32 - boxSize, i*32 - boxSize);
		}
	}

	for (int i = 0; i < MessegeHeight; i++)
	{
		for (int j = 0; j < MessageWidth; j++)
		{
			if (i == 0 && j == 0)
				StatMessegeBox->FrameRender(g_hDC, 50 + j * 15, 100 + i * 15, 0, 0);
			else if (i == 0 && j == MessageWidth - 1)
				StatMessegeBox->FrameRender(g_hDC, 50 + j * 15, 100 + i * 15, 2, 0);
			else if (i == MessegeHeight - 1 && j == 0)
				StatMessegeBox->FrameRender(g_hDC, 50 + j * 15, 100 + i * 15, 0, 2);
			else if (i == MessegeHeight - 1 && j == MessageWidth - 1)
				StatMessegeBox->FrameRender(g_hDC, 50 + j * 15, 100 + i * 15, 2, 2);
			else if (i == 0 && (j != 0 || j != MessageWidth - 1))
				StatMessegeBox->FrameRender(g_hDC, 50 + j * 15, 100 + i * 15, 1, 0);
			else if ((i != 0 || i != MessegeHeight - 1) && j == 0)
				StatMessegeBox->FrameRender(g_hDC, 50 + j * 15, 100 + i * 15, 0, 1);
			else if ((i != 0 || i != MessegeHeight - 1) && j == MessageWidth - 1)
				StatMessegeBox->FrameRender(g_hDC, 50 + j * 15, 100 + i * 15, 2, 1);
			else if (i == MessegeHeight - 1 && (j != 0 || j != MessageWidth - 1))
				StatMessegeBox->FrameRender(g_hDC, 50 + j * 15, 100 + i * 15, 1, 2);
		}
	}

	for (int i = 0; i < MessegeHeight; i++)
	{
		for (int j = 0; j < MessageWidth; j++)
		{
			if (i == 0 && j == 0)
				StatMessegeBox->FrameRender(g_hDC, 550 + j * 15, 100 + i * 15, 0, 0);
			else if (i == 0 && j == MessageWidth - 1)
				StatMessegeBox->FrameRender(g_hDC, 550 + j * 15, 100 + i * 15, 2, 0);
			else if (i == MessegeHeight - 1 && j == 0)
				StatMessegeBox->FrameRender(g_hDC, 550 + j * 15, 100 + i * 15, 0, 2);
			else if (i == MessegeHeight - 1 && j == MessageWidth - 1)
				StatMessegeBox->FrameRender(g_hDC, 550 + j * 15, 100 + i * 15, 2, 2);
			else if (i == 0 && (j != 0 || j != MessageWidth - 1))
				StatMessegeBox->FrameRender(g_hDC, 550 + j * 15, 100 + i * 15, 1, 0);
			else if ((i != 0 || i != MessegeHeight - 1) && j == 0)
				StatMessegeBox->FrameRender(g_hDC, 550 + j * 15, 100 + i * 15, 0, 1);
			else if ((i != 0 || i != MessegeHeight - 1) && j == MessageWidth - 1)
				StatMessegeBox->FrameRender(g_hDC, 550 + j * 15, 100 + i * 15, 2, 1);
			else if (i == MessegeHeight - 1 && (j != 0 || j != MessageWidth - 1))
				StatMessegeBox->FrameRender(g_hDC, 550 + j * 15, 100 + i * 15, 1, 2);
		}
	}

	sprintf(ch_buffer, "L V : %d", Player->GetLV());
	SetTextColor(g_hDC, RGB(255, 255, 255));
	TextOut(g_hDC, 150, 150, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "H P : %d", Player->GetHP());
	SetTextColor(g_hDC, RGB(255, 255, 255));
	TextOut(g_hDC, 150, 200, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "ATK : %d + (%d)", Player->GetATK(),Player->GetItemATK());
	SetTextColor(g_hDC, RGB(255, 255, 255));
	TextOut(g_hDC, 150, 250, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "DEF : %d + (%d)", Player->GetDEF(),Player->GetItemDEF());
	SetTextColor(g_hDC, RGB(255, 255, 255));
	TextOut(g_hDC, 150, 300, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "EXP : %d", Player->GetEXP());
	SetTextColor(g_hDC, RGB(255, 255, 255));
	TextOut(g_hDC, 150, 350, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "MAXEXP : %d", Player->GetMAXEXP());
	SetTextColor(g_hDC, RGB(255, 255, 255));
	TextOut(g_hDC, 150, 400, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "M O N E Y : %d 루크", Player->GetMoney());
	SetTextColor(g_hDC, RGB(255, 255, 255));
	TextOut(g_hDC, 150, 450, ch_buffer, strlen(ch_buffer));

	Finger->Render(g_hDC, Finger->GetPosX(), Finger->GetPosY(),30,30);

	for (auto iter = Player->GetPlayerInven().begin(); iter != Player->GetPlayerInven().end(); iter++)
	{
		string buffer = (*iter)->GetName();
		(*iter)->GetImage()->Render(g_hDC, 600, InvenHeight, 40, 40);
		if ((*iter)->GetIsWearSword() || (*iter)->GetIsWearAmor())
		{
			buffer += " (착용중)";
			SetTextColor(g_hDC, RGB(255, 255, 255));
			TextOut(g_hDC, 650, InvenHeight, buffer.c_str(), strlen(buffer.c_str()));
		}
		else
		{
			SetTextColor(g_hDC, RGB(255, 255, 255));
			TextOut(g_hDC, 650, InvenHeight, buffer.c_str(), strlen(buffer.c_str()));
		}
		sprintf_s(ch_buffer, "%d 개", (*iter)->GetAmount());
		SetTextColor(g_hDC, RGB(255, 255, 255));
		TextOut(g_hDC, 900, InvenHeight, ch_buffer, strlen(ch_buffer));
		InvenHeight += 50;
		
	}

	if (isFullHP)
	{
		//SetBkMode(g_hDC, BKMODE_LAST);
		TextOut(g_hDC, WINSIZEX/2, 30, "체력이 가득입니다.", strlen("체력이 가득입니다."));
	}

}
