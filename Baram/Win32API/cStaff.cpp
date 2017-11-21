#include "stdafx.h"
#include "cStaff.h"

void cStaff::Setup()
{
}

void cStaff::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
}

void cStaff::Render()
{
	SetTextColor(g_hDC, RGB(90, 200, 120));
	TextOut(g_hDC, WINSIZEX / 2, WINSIZEY / 2, "½ºÅ×ÇÁ¾À", strlen("½ºÅ×ÇÁ¾À"));
}

void cStaff::Release()
{
}
