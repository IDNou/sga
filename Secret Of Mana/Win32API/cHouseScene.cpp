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

	Store = new cStore;

	isBuy = false;

}

void cHouseScene::Update()
{
	if (!isBuy)
		Player->Update();
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
		isBuy = true;
	}

	if (g_pKeyManager->isStayKeyDown(VK_ESCAPE))
	{
		isBuy = false;
	}
}

void cHouseScene::Render()
{
	BackGround->Render(EmptyBuffer->GetMemDC());
	Player->Render(EmptyBuffer->GetMemDC());
	RectangleMake(EmptyBuffer->GetMemDC(), 450, 50, 200, 200);
	if (isBuy)
		Store->Render(EmptyBuffer->GetMemDC());
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort);
}

void cHouseScene::Release()
{
}
