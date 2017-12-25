#include "stdafx.h"
#include "cTitleScene.h"


void cTitleScene::Setup()
{
	alhpa = 255;
	isSwitch = false;
	g_pSoundManager->Play("TitleSound");
}

void cTitleScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		g_pPlayerManager->GetPlayer()->SetHp(g_pPlayerManager->GetPlayer()->GetMAXHP());
		g_pSceneManager->SetNextScene(SLIST_PLAY);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown('2'))
	{
		g_pSceneManager->SetNextScene(SLIST_PLAY2);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown('M'))
	{
		g_pSceneManager->SetNextScene(SLIST_MAPTOOL);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);

	if (isSwitch) {
		alhpa+= 5;
	}
	else
	{
		alhpa-= 5;
	}

	if (alhpa < 10) {
		isSwitch = true;
	}
	else if (alhpa > 255)
	{
		isSwitch = false;
	}
}

void cTitleScene::Render()
{
	g_pImageManager->Render("TitleBG", g_hDC);
	g_pImageManager->AlphaRender("Start", g_hDC, WINSIZEX / 2 - 100, WINSIZEY - 150, alhpa);
}

void cTitleScene::Release()
{
}
