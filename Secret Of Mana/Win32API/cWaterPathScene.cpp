#include "stdafx.h"
#include "cWaterPathScene.h"
#include "cMonster.h"
#include "cPlayer.h"

void cWaterPathScene::Setup()
{

	BackGround = g_pImageManager->FindImage("WaterAndPandoraPath");
	BackGround_Magenta = g_pImageManager->FindImage("WaterAndPandoraPath_Magenta");
	EmptyBuffer = g_pImageManager->FindImage("EmptyBuffer");
	Player = g_pPlayerManager->GetPlayer();
	Player->SetPosX(800);
	Player->SetPosY(50);
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);

	g_pSoundManager->Play("WaterPath");
}

void cWaterPathScene::Update()
{
	Player->Update();
	ViewPort = ViewPortMake(Player->GetPosX(), Player->GetPosY(), WINSIZEX / 2, WINSIZEY / 2, BackGround->GetWidth(), BackGround->GetHeight());
	Player->SetViewPort(ViewPort);

	RECT rt;
	if (IntersectRect(&rt,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10), 
		&RectMake(670, 1650, 35, 25)))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_BOSSMAP);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (IntersectRect(&rt,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10),
		&RectMake(810, 0, 40, 30)))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_PLAY);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

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
	RectangleMake(EmptyBuffer->GetMemDC(), 670, 1650, 30, 20);
	RectangleMake(EmptyBuffer->GetMemDC(), 810, 0, 40, 30);
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort, WINSIZEX, WINSIZEY);
}

void cWaterPathScene::Release()
{
}
