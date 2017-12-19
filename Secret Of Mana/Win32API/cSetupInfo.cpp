#include "stdafx.h"
#include "cSetupInfo.h"
#include "cPlayer.h"

void cSetupInfo::Setup()
{
	Player = g_pPlayerManager->GetPlayer();
	BackGround = g_pImageManager->AddImage("BackGround", "images/SetupInfoBackGround.png", 32, 32, true, RGB(255, 0, 255));
	StatMessegeBox = g_pImageManager->AddFrameImage("MessegeBox", "images/StatMessegeBox.png", 45, 45, 3, 3, true, RGB(255, 0, 255));
	boxSize = 0;
	InvenWidth = 600;
	InvenHeight = 150;

}

void cSetupInfo::Update()
{
	if (boxSize >= 32)
	{
		boxSize = 0;
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

	HFONT hFont = CreateFont(30, 0, 0, 0, FW_HEAVY, 0, HANGEUL_CHARSET, 0, 0, 0, 0, 0, 0, TEXT("³»²¨"));
	HFONT OldFont = (HFONT)SelectObject(g_hDC, hFont);
	SetTextColor(g_hDC, RGB(240, 240, 240));

	sprintf(ch_buffer, "L V : %d", Player->GetLV());
	TextOut(g_hDC, 150, 150, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "H P : %d", Player->GetHP());
	TextOut(g_hDC, 150, 200, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "ATK : %d", Player->GetATK());
	TextOut(g_hDC, 150, 250, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "DEF : %d", Player->GetDEF());
	TextOut(g_hDC, 150, 300, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "EXP : %d", Player->GetEXP());
	TextOut(g_hDC, 150, 350, ch_buffer, strlen(ch_buffer));

	sprintf(ch_buffer, "M O N E Y : %d ·çÅ©", Player->GetMoney());
	TextOut(g_hDC, 150, 400, ch_buffer, strlen(ch_buffer));

	DeleteObject(SelectObject(g_hDC, hFont));
	DeleteObject(OldFont);
	DeleteObject(hFont);

	for (auto iter = Player->GetPlayerInven().begin(); iter != Player->GetPlayerInven().end(); iter++)
	{
		string buffer = (*iter)->GetName();
		(*iter)->GetImage()->Render(g_hDC, 600, InvenHeight, 40, 40);
		TextOut(g_hDC, 650, InvenHeight, buffer.c_str(), strlen(buffer.c_str()));
		sprintf_s(ch_buffer, "%d °³", (*iter)->GetAmount());
		TextOut(g_hDC, 900, InvenHeight, ch_buffer, strlen(ch_buffer));
		InvenHeight += 50;
	}

}

void cSetupInfo::Release()
{
}
