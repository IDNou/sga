#include "stdafx.h"
#include "cTitleScene.h"


void cTitleScene::Setup()
{
	
}

void cTitleScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		g_pSceneManager->SetNextScene(SLIST_MARIO);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown('2'))
	{
		g_pSceneManager->SetNextScene(SLIST_FOTRESS);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown('3'))
	{
		g_pSceneManager->SetNextScene(SLIST_2048);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
}

void cTitleScene::Render()
{
	TextOut(g_hDC, WINSIZEX / 2-50, WINSIZEY / 2 - 100, "1. 마리오", strlen("1. 마리오"));
	TextOut(g_hDC, WINSIZEX / 2-50, WINSIZEY / 2 , "2. 포트리스", strlen("2. 포트리스"));
	TextOut(g_hDC, WINSIZEX / 2-50, WINSIZEY / 2 + 100, "3. 1945", strlen("3. 1945"));
}

void cTitleScene::Release()
{
	
}
