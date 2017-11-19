#include "stdafx.h"
#include "cDungeon1.h"


void cDungeon1::Setup()
{
	savePlayer.ATK = g_pIniData->LoadDataInteger("charater.ini", "stat", "ATK");
	savePlayer.DEF = g_pIniData->LoadDataInteger("charater.ini", "stat", "DEF");
	savePlayer.HP = g_pIniData->LoadDataInteger("charater.ini", "stat", "HP");
	savePlayer.Kit = g_pIniData->LoadDataInteger("charater.ini", "stat", "Kit");
	savePlayer.MaNaKit = g_pIniData->LoadDataInteger("charater.ini", "stat", "MaNaKit");
	savePlayer.Money = g_pIniData->LoadDataInteger("charater.ini", "stat", "Money");

	//g_pSoundManager->Play("buyeu", 1.0f);
}

void cDungeon1::Update()
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
		savePlayer.Kit++;
		savePlayer.Money += 100;

		sprintf(buffer, "%d", savePlayer.Kit);
		g_pIniData->AddData("stat", "Kit", buffer);
		g_pIniData->IniSave("charater.ini");

		sprintf(buffer, "%d", savePlayer.Money);
		g_pIniData->AddData("stat", "Money", buffer);
		g_pIniData->IniSave("charater.ini");
	}
	else if (PtInRect(&RectMakeCenter(250, 250, 300, 50), g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		char buffer[256];
		g_pSoundManager->Play("coin", 1.0f);
		savePlayer.MaNaKit++;

		sprintf(buffer, "%d", savePlayer.MaNaKit);
		g_pIniData->AddData("stat", "MaNaKit", buffer);
		g_pIniData->IniSave("charater.ini");
	}
}

void cDungeon1::Render()
{
	char buffer[256];

	RectangleMakeCenter(g_hDC, 250, 150, 300, 50);
	TextOut(g_hDC, 220, 150, "1. 물약", strlen("1. 물약"));
	RectangleMakeCenter(g_hDC, 250, 250, 300, 50);
	TextOut(g_hDC, 220, 250, "1. 마나물약", strlen("1. 마나물약"));

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


	TextOut(g_hDC, WINSIZEX - 100, WINSIZEY - 100, "1번씬", strlen("1번씬"));
}

void cDungeon1::Release()
{
}
