#include "stdafx.h"
#include "cDungeon3.h"


void cDungeon3::Setup()
{
	vector<enermy>::iterator iterEraser = vecTest.begin();

	while (iterEraser != vecTest.end())
	{
		iterEraser = vecTest.erase(iterEraser);
	}

	for (int i = 0; i < 3; i++)
	{
		Test.PosX = GetRandom(100, WINSIZEX - 100);
		Test.PosY = GetRandom(100, WINSIZEY - 100);
		Test.ATK = GetRandom(1, 5);
		Test.Money = GetRandom(100, 200);
		Test.isDie = false;
		vecTest.push_back(Test);
	}

	savePlayer.playerImage = g_pImageManager->FindImage("300");
	savePlayer.ATK = g_pIniData->LoadDataInteger("charater.ini", "stat", "ATK");
	savePlayer.DEF = g_pIniData->LoadDataInteger("charater.ini", "stat", "DEF");
	savePlayer.HP = g_pIniData->LoadDataInteger("charater.ini", "stat", "HP");
	savePlayer.Kit = g_pIniData->LoadDataInteger("charater.ini", "stat", "Kit");
	savePlayer.MaNaKit = g_pIniData->LoadDataInteger("charater.ini", "stat", "MaNaKit");
	savePlayer.Money = g_pIniData->LoadDataInteger("charater.ini", "stat", "Money");

	if (g_pSoundManager->IsPlaySound("buyeu"))
		g_pSoundManager->Stop("buyeu");

	g_pSoundManager->Play("dungeon1", 1.0f);
}

void cDungeon3::Update()
{
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);

	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
	{
		savePlayer.playerImage->SetPosX(savePlayer.playerImage->GetPosX() - 3);
	}
	if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		savePlayer.playerImage->SetPosX(savePlayer.playerImage->GetPosX() + 3);
	}
	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		savePlayer.playerImage->SetPosY(savePlayer.playerImage->GetPosY() - 3);
	}
	if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		savePlayer.playerImage->SetPosY(savePlayer.playerImage->GetPosY() + 3);
	}

	RECT ct;
	for (auto iter = vecTest.begin(); iter != vecTest.end(); ++iter)
	{
		if (IntersectRect(&ct, &RectMakeCenter(iter->PosX, iter->PosY, 100, 100),
			&RectMake(savePlayer.playerImage->GetPosX() + savePlayer.playerImage->GetWidth() / 2,
				savePlayer.playerImage->GetPosY() + savePlayer.playerImage->GetHeight() / 2,
				savePlayer.playerImage->GetWidth(),
				savePlayer.playerImage->GetHeight())))
		{
			char buffer[256];

			savePlayer.HP -= iter->ATK;
			sprintf(buffer, "%d", savePlayer.HP);
			g_pIniData->AddData("stat", "HP", buffer);
			g_pIniData->IniSave("charater.ini");

			savePlayer.Money += iter->Money;
			sprintf(buffer, "%d", savePlayer.Money);
			g_pIniData->AddData("stat", "Money", buffer);
			g_pIniData->IniSave("charater.ini");
			iter->isDie = true;
		}
	}

	for (auto iter = vecTest.begin(); iter != vecTest.end(); )
	{
		if (iter->isDie)
			iter = vecTest.erase(iter);
		else
			++iter;
	}
}

void cDungeon3::Render()
{
	char buffer[256];

	for (auto iter = vecTest.begin(); iter != vecTest.end(); ++iter)
	{
		EllipseMakeCenter(g_hDC, iter->PosX, iter->PosY, 100, 100);
	}

	RectangleMake(g_hDC, savePlayer.playerImage->GetPosX() + savePlayer.playerImage->GetWidth() / 2,
		savePlayer.playerImage->GetPosY() + savePlayer.playerImage->GetHeight() / 2,
		savePlayer.playerImage->GetWidth(),
		savePlayer.playerImage->GetHeight());
	savePlayer.playerImage->Render(g_hDC,
		savePlayer.playerImage->GetPosX() + savePlayer.playerImage->GetWidth() / 2,
		savePlayer.playerImage->GetPosY() + savePlayer.playerImage->GetHeight() / 2);

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

	TextOut(g_hDC, WINSIZEX - 100, WINSIZEY - 100, "3¹ø¾À", strlen("3¹ø¾À"));
}

void cDungeon3::Release()
{
}
