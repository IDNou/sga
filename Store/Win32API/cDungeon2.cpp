#include "stdafx.h"
#include "cDungeon2.h"


void cDungeon2::Setup()
{
	savePlayer.ATK = g_pIniData->LoadDataInteger("charater.ini", "stat", "ATK");
	savePlayer.DEF = g_pIniData->LoadDataInteger("charater.ini", "stat", "DEF");
	savePlayer.HP = g_pIniData->LoadDataInteger("charater.ini", "stat", "HP");
	savePlayer.Kit = g_pIniData->LoadDataInteger("charater.ini", "stat", "Kit");
	savePlayer.MaNaKit = g_pIniData->LoadDataInteger("charater.ini", "stat", "MaNaKit");
	savePlayer.Money = g_pIniData->LoadDataInteger("charater.ini", "stat", "Money");

	//g_pSoundManager->Play("buyeu", 1.0f);
}

void cDungeon2::Update()
{
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);

	if (PtInRect(&RectMakeCenter(250, 150, 300, 50), g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		char buffer[256];
		g_pSoundManager->Play("coin", 1.0f);
		savePlayer.DEF += 5;

		sprintf(buffer, "%d", savePlayer.DEF);
		g_pIniData->AddData("stat", "DEF", buffer);
		g_pIniData->IniSave("charater.ini");
	}
	else if (PtInRect(&RectMakeCenter(250, 250, 300, 50), g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		char buffer[256];
		g_pSoundManager->Play("coin", 1.0f);
		savePlayer.DEF += 10;

		sprintf(buffer, "%d", savePlayer.DEF);
		g_pIniData->AddData("stat", "DEF", buffer);
		g_pIniData->IniSave("charater.ini");
	}

	if (PtInRect(&RectMakeCenter(250, 450, 300, 50), g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		char buffer[256];
		g_pSoundManager->Play("coin", 1.0f);
		savePlayer.ATK += 5;

		sprintf(buffer, "%d", savePlayer.ATK);
		g_pIniData->AddData("stat", "ATK", buffer);
		g_pIniData->IniSave("charater.ini");
	}
	else if (PtInRect(&RectMakeCenter(250, 550, 300, 50), g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		char buffer[256];
		g_pSoundManager->Play("coin", 1.0f);
		savePlayer.ATK += 10;

		sprintf(buffer, "%d", savePlayer.ATK);
		cout << buffer << endl;
		g_pIniData->AddData("stat", "ATK", buffer);
		g_pIniData->IniSave("charater.ini");
	}
}

void cDungeon2::Render()
{
	char buffer[256];

	RectangleMakeCenter(g_hDC, 250, 150, 300, 50);
	TextOut(g_hDC, 220, 150, "1. Ãµ°©¿Ê  DEF+5", strlen("1. Ãµ°©¿Ê  DEF+5"));
	RectangleMakeCenter(g_hDC, 250, 250, 300, 50);
	TextOut(g_hDC, 220, 250, "2. Ã¶°©¿Ê  DEF+10", strlen("2. Ã¶°©¿Ê  DEF+10"));

	RectangleMakeCenter(g_hDC, 250, 450, 300, 50);
	TextOut(g_hDC, 220, 450, "1. ¸ñ°Ë   ATK+5", strlen("1. ¸ñ°Ë   ATK+5"));
	RectangleMakeCenter(g_hDC, 250, 550, 300, 50);
	TextOut(g_hDC, 220, 550, "2. Ã¶°Ë   ATK+10", strlen("2. Ã¶°Ë   ATK+10"));

	RectangleMake(g_hDC, WINSIZEX - 200, 50, 150, 500);
	sprintf(buffer, "Money : %d", savePlayer.Money);
	TextOut(g_hDC, WINSIZEX - 150, 100, buffer, strlen(buffer));
	sprintf(buffer, "ATK : %d", savePlayer.ATK);
	TextOut(g_hDC, WINSIZEX - 150, 150, buffer, strlen(buffer));
	sprintf(buffer, "DEF : %d", savePlayer.DEF);
	TextOut(g_hDC, WINSIZEX - 150, 200, buffer, strlen(buffer));
	sprintf(buffer, "HP : %d", savePlayer.HP);
	TextOut(g_hDC, WINSIZEX - 150, 250, buffer, strlen(buffer));
	sprintf(buffer, "Kit : %d", savePlayer.Kit);
	TextOut(g_hDC, WINSIZEX - 150, 300, buffer, strlen(buffer));
	sprintf(buffer, "MaNaKit : %d", savePlayer.MaNaKit);
	TextOut(g_hDC, WINSIZEX - 150, 350, buffer, strlen(buffer));

	TextOut(g_hDC, WINSIZEX - 100, WINSIZEX - 100, "2¹ø¾À", strlen("2¹ø¾À"));
}

void cDungeon2::Release()
{
}
