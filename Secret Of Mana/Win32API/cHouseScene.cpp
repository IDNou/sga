#include "stdafx.h"
#include "cHouseScene.h"
#include "cPlayer.h"
#include "cStore.h"


void cHouseScene::Setup()
{
	BackGround = g_pImageManager->FindImage("House");
	BackGround_Magenta = g_pImageManager->FindImage("House_Magenta");
	EmptyBuffer = g_pImageManager->FindImage("EmptyBuffer");

	Player = g_pPlayerManager->GetPlayer();
	Player->SetPosX(200);
	Player->SetPosY(300);
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);

	StoreNPC = g_pImageManager->FindImage("StoreNPC");
	StoreNPC->SetPosX(510);
	StoreNPC->SetPosY(100);

	Store = new cStore;

	isBuy = false;
	count = 5;

}

void cHouseScene::Update()
{
	if (!isBuy)
	{
		Player->Update();

		if (count < 0)
		{
			count = 5;
			StoreNPC->SetFrameX(StoreNPC->GetFrameX() + 1);
			if (StoreNPC->GetMaxFrameX() < StoreNPC->GetFrameX())
			{
				StoreNPC->SetFrameX(0);
			}
		}

		count--;
	}
	else
		Store->Update();
	ViewPort = ViewPortMake(Player->GetPosX(), Player->GetPosY(), WINSIZEX / 2, WINSIZEY / 2, BackGround->GetWidth(), BackGround->GetHeight());
	Player->SetViewPort(ViewPort);

	RECT rt;
	if (IntersectRect(&rt,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() - 10,10,10),
		&RectMake(450, 50, 200, 200)) && Player->GetIsBuy())
	{
		Store->Setup();
		Player->SetIsBuy(false);
		StoreNPC->SetFrameX(0);
		isBuy = true;
	}
	else if (IntersectRect(&rt,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() - 10, 10, 10),
		&RectMake(250, 370, 140, 50)))
	{
		Place["Place"]["NAME"] = "STORE";
		ofstream Input_Place;
		Input_Place.open("PlayerPlace.json");
		Input_Place << Place;
		Input_Place.close();
		g_pSceneManager->SetNextScene(SLIST_PLAY);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	if (g_pKeyManager->isStayKeyDown(VK_ESCAPE))
	{
		isBuy = false;
		count = 5;
	}
}

void cHouseScene::Render()
{
	BackGround->Render(EmptyBuffer->GetMemDC());
	Player->Render(EmptyBuffer->GetMemDC());
	StoreNPC->FrameRender(EmptyBuffer->GetMemDC(),StoreNPC->GetPosX(),StoreNPC->GetPosY(),StoreNPC->GetFrameX(),StoreNPC->GetFrameY());
	//RectangleMake(EmptyBuffer->GetMemDC(), 450, 50, 200, 200);
	//RectangleMake(EmptyBuffer->GetMemDC(), 250, 370, 140, 50);
	if (isBuy)
		Store->Render(EmptyBuffer->GetMemDC());
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort);
}

void cHouseScene::Release()
{
}
