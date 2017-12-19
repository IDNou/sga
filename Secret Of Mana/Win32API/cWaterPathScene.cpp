#include "stdafx.h"
#include "cWaterPathScene.h"
#include "cMonster.h"
#include "cPlayer.h"

void cWaterPathScene::Setup()
{

	BackGround = g_pImageManager->FindImage("WaterAndPandoraPath");
	BackGround_Magenta = g_pImageManager->FindImage("WaterAndPandoraPath_Magenta");
	EmptyBuffer = g_pImageManager->AddEmptyImage("asdf",BackGround->GetWidth(),BackGround->GetHeight());
	Player = g_pPlayerManager->GetPlayer();
	Player->SetPosX(400);
	Player->SetPosY(40);
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);
	Player->SetTerrainWidth(BackGround->GetWidth());
	Player->SetTerrainHeight(BackGround->GetHeight());

	g_pSoundManager->Play("WaterPath");
}

void cWaterPathScene::Update()
{
	Player->Update();
	ViewPort = ViewPortMake(Player->GetPosX(), Player->GetPosY(), WINSIZEX / 2, WINSIZEY / 2, BackGround->GetWidth(), BackGround->GetHeight());

	if (g_pKeyManager->isStayKeyDown(VK_ESCAPE))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
}

void cWaterPathScene::Render()
{
	BackGround->Render(EmptyBuffer->GetMemDC());
	Player->Render(EmptyBuffer->GetMemDC());
	RectangleMake(EmptyBuffer->GetMemDC(), 1180, 1430, 35, 25);
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort, WINSIZEX, WINSIZEY);
}

void cWaterPathScene::Release()
{
}
