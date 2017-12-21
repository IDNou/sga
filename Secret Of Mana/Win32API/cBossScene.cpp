#include "stdafx.h"
#include "cBossScene.h"
#include "cPlayer.h"
#include "cMonster.h"

void cBossScene::Setup()
{
	BackGround = g_pImageManager->FindImage("BossMap");
	BackGround_Magenta = g_pImageManager->FindImage("BossMap_Magenta");
	EmptyBuffer = g_pImageManager->FindImage("EmptyBuffer");

	Player = g_pPlayerManager->GetPlayer();
	Player->SetPosX(200);
	Player->SetPosY(100);
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);
}

void cBossScene::Update()
{
	Player->Update();
	ViewPort = ViewPortMake(Player->GetPosX(), Player->GetPosY(), WINSIZEX / 2, WINSIZEY / 2, BackGround->GetWidth(), BackGround->GetHeight());
	Player->SetViewPort(ViewPort);


}

void cBossScene::Render()
{
	BackGround->Render(EmptyBuffer->GetMemDC());
	Player->Render(EmptyBuffer->GetMemDC());
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort);
}

void cBossScene::Release()
{
}
