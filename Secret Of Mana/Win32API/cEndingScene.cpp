#include "stdafx.h"
#include "cEndingScene.h"


void cEndingScene::Setup()
{
}

void cEndingScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
}

void cEndingScene::Render()
{
}

void cEndingScene::Release()
{
}
