#include "stdafx.h"
#include "cLoad.h"

void cLoad::Setup()
{
}

void cLoad::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
}

void cLoad::Render()
{
	SetTextColor(g_hDC, RGB(90, 200, 120));
	TextOut(g_hDC, WINSIZEX / 2, WINSIZEY / 2, "·Îµå¾À", strlen("·Îµå¾À"));
}

void cLoad::Release()
{
}
