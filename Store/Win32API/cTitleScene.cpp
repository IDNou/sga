#include "stdafx.h"
#include "cTitleScene.h"


void cTitleScene::Setup()
{
	store1 = g_pImageManager->FindImage("2");
	store2 = g_pImageManager->FindImage("3");
	dungeon1 = g_pImageManager->FindImage("0");
	dungeon2 = g_pImageManager->FindImage("1");
	player.playerImage = g_pImageManager->FindImage("4");
	player.playerImage->SetPosX(WINSIZEX / 2 - player.playerImage->GetWidth() -100);
	player.playerImage->SetPosY(WINSIZEY / 2 - player.playerImage->GetHeight());
	player.ATK = g_pIniData->LoadDataInteger("charater.ini","stat","ATK");
	player.DEF = g_pIniData->LoadDataInteger("charater.ini", "stat", "DEF");
	player.HP = g_pIniData->LoadDataInteger("charater.ini", "stat", "HP");
	player.Kit = g_pIniData->LoadDataInteger("charater.ini", "stat", "Kit");
	player.MaNaKit = g_pIniData->LoadDataInteger("charater.ini", "stat", "MaNaKit");
	player.Money = g_pIniData->LoadDataInteger("charater.ini", "stat", "Money");

	if(!g_pSoundManager->IsPlaySound("buyeu"))
		g_pSoundManager->Play("buyeu", 1.0f);
	if (g_pSoundManager->IsPlaySound("dungeon1"))
		g_pSoundManager->Stop("dungeon1");
	else if(g_pSoundManager->IsPlaySound("dungeon2"))
		g_pSoundManager->Stop("dungeon2");
}

void cTitleScene::Update()
{
	////물약상점
	//if (g_pKeyManager->isOnceKeyDown('2'))
	//{
	//	g_pSceneManager->SetNextScene(SLIST_DUNGEON1);
	//	g_pSceneManager->ChangeScene(SLIST_LOADING);
	//}
	////장비상점
	//else if (g_pKeyManager->isOnceKeyDown('3'))
	//{
	//	g_pSceneManager->SetNextScene(SLIST_DUNGEON2);
	//	g_pSceneManager->ChangeScene(SLIST_LOADING);
	//}
	////던전1
	//else if (g_pKeyManager->isOnceKeyDown('0'))
	//{
	//	g_pSceneManager->SetNextScene(SLIST_DUNGEON3);
	//	g_pSceneManager->ChangeScene(SLIST_LOADING);
	//}
	////던전2
	//else if (g_pKeyManager->isOnceKeyDown('1'))
	//{
	//	g_pSceneManager->SetNextScene(SLIST_DUNGEON4);
	//	g_pSceneManager->ChangeScene(SLIST_LOADING);
	//}
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);

	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
	{
		player.playerImage->SetPosX(player.playerImage->GetPosX() - 3);
	}
	if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		player.playerImage->SetPosX(player.playerImage->GetPosX() + 3);
	}
	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		player.playerImage->SetPosY(player.playerImage->GetPosY() - 3);
	}
	if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		player.playerImage->SetPosY(player.playerImage->GetPosY() + 3);
	}

	RECT rt;
	if (IntersectRect(&rt,
		&RectMake(player.playerImage->GetPosX() + player.playerImage->GetWidth() / 2,
			player.playerImage->GetPosY() + player.playerImage->GetHeight() / 2,
			player.playerImage->GetWidth(),
			player.playerImage->GetHeight()),
		&RectMake(50, 50, store1->GetWidth(), store1->GetHeight())))
	{
		g_pSceneManager->SetNextScene(SLIST_DUNGEON1);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (IntersectRect(&rt,
		&RectMake(player.playerImage->GetPosX() + player.playerImage->GetWidth() / 2,
			player.playerImage->GetPosY() + player.playerImage->GetHeight() / 2,
			player.playerImage->GetWidth(),
			player.playerImage->GetHeight()),
		&RectMake(50, WINSIZEY - 150, store2->GetWidth(), store2->GetHeight())))
	{
		g_pSceneManager->SetNextScene(SLIST_DUNGEON2);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (IntersectRect(&rt,
		&RectMake(player.playerImage->GetPosX() + player.playerImage->GetWidth() / 2,
			player.playerImage->GetPosY() + player.playerImage->GetHeight() / 2,
			player.playerImage->GetWidth(),
			player.playerImage->GetHeight()),
		&RectMake(WINSIZEX - 350, 50, dungeon1->GetWidth(), dungeon2->GetHeight())))
	{
		g_pSceneManager->SetNextScene(SLIST_DUNGEON3);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (IntersectRect(&rt,
		&RectMake(player.playerImage->GetPosX() + player.playerImage->GetWidth() / 2,
			player.playerImage->GetPosY() + player.playerImage->GetHeight() / 2,
			player.playerImage->GetWidth(),
			player.playerImage->GetHeight()),
		&RectMake(WINSIZEX - 350, WINSIZEY - 150, dungeon2->GetWidth(), dungeon2->GetHeight())))
	{
		g_pSceneManager->SetNextScene(SLIST_DUNGEON4);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
}

void cTitleScene::Render()
{
	char buffer[256];

	//각 입구들
	RectangleMake(g_hDC, 50, 50, store1->GetWidth(), store1->GetHeight());
	store1->Render(g_hDC, 50, 50);
	RectangleMake(g_hDC, 50, WINSIZEY - 150, store2->GetWidth(), store2->GetHeight());
	store2->Render(g_hDC, 50, WINSIZEY - 150);
	RectangleMake(g_hDC, WINSIZEX - 350, 50, dungeon1->GetWidth(), dungeon2->GetHeight());
	dungeon1->Render(g_hDC, WINSIZEX - 350, 50);
	RectangleMake(g_hDC, WINSIZEX - 350, WINSIZEY - 150, dungeon2->GetWidth(), dungeon2->GetHeight());
	dungeon2->Render(g_hDC, WINSIZEX - 350, WINSIZEY - 150);


	//스탯보여주는곳
	RectangleMake(g_hDC, WINSIZEX - 200, 50, 150, 500);
	sprintf(buffer, "Money : %d", player.Money);
	TextOut(g_hDC, WINSIZEX - 150, 100, buffer, strlen(buffer));
	sprintf(buffer, "ATK : %d", player.ATK);
	TextOut(g_hDC, WINSIZEX - 150, 150, buffer, strlen(buffer));
	sprintf(buffer, "DEF : %d", player.DEF);
	TextOut(g_hDC, WINSIZEX - 150, 200, buffer, strlen(buffer));
	sprintf(buffer, "HP : %d", player.HP);
	TextOut(g_hDC, WINSIZEX - 150, 250, buffer, strlen(buffer));
	sprintf(buffer, "Kit : %d", player.Kit);
	TextOut(g_hDC, WINSIZEX - 150, 300, buffer, strlen(buffer));
	sprintf(buffer, "MaNaKit : %d", player.MaNaKit);
	TextOut(g_hDC, WINSIZEX - 150, 350, buffer, strlen(buffer));


	//플레이어
	RectangleMake(g_hDC, player.playerImage->GetPosX() + player.playerImage->GetWidth() / 2,
		player.playerImage->GetPosY() + player.playerImage->GetHeight() / 2,
		player.playerImage->GetWidth(),
		player.playerImage->GetHeight());
	player.playerImage->Render(g_hDC,
		player.playerImage->GetPosX() + player.playerImage->GetWidth() / 2,
		player.playerImage->GetPosY() + player.playerImage->GetHeight() / 2);

	//TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
}

void cTitleScene::Release()
{
}
