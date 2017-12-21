#include "stdafx.h"
#include "cMainGame.h"

// 씬 헤더파일들 추가
#include "cTitleScene.h"
#include "cPlayScene.h"
#include "cLoadingScene.h"
#include "cDijkstraTest.h"
#include "cMapTool.h"
#include "cWaterPathScene.h"
#include "cSetupInfo.h"
#include "cHouseScene.h"
#include "cBossScene.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
}

void cMainGame::Setup()
{
	isPause = false;

	// 씬 추가
	g_pSceneManager->AddScene(SLIST_LOADING, new cLoadingScene);
	g_pSceneManager->AddScene(SLIST_TITLE, new cTitleScene);
	g_pSceneManager->AddScene(SLIST_MAPTOOL, new cMapTool);
	g_pSceneManager->AddScene(SLIST_PLAY, new cPlayScene);
	g_pSceneManager->AddScene(SLIST_PLAY2, new cDijkstraTest);
	g_pSceneManager->AddScene(SLIST_WATERPATH, new cWaterPathScene);
	g_pSceneManager->AddScene(SLIST_HOUSE, new cHouseScene);
	g_pSceneManager->AddScene(SLIST_BOSSMAP, new cBossScene);

	// 처음 시작 씬 셋팅
	g_pSceneManager->ChangeScene(SLIST_LOADING);

	g_pItemManager->Start();

	g_pPlayerManager->Start();

	g_pMonsterManager->Start();

	//인벤에 아이템을 강제로 삽입
	g_pPlayerManager->GetPlayer()->GetPlayerInven().push_back(g_pItemManager->FindItem("ManaSword"));
	g_pPlayerManager->GetPlayer()->GetPlayerInven().push_back(g_pItemManager->FindItem("Candy"));


	// 이전에 미리등록
	
	SetupInfo = new cSetupInfo;


}

void cMainGame::Update()
{
	cGameNode::Update();

	if (!isPause)
		g_pSceneManager->Update();
	else
		SetupInfo->Update();

	if (g_pKeyManager->isOnceKeyDown('P'))
	{
		if (!isPause)
		{
			isPause = true;
			SetupInfo->Setup();
		}
		else
		{
			isPause = false;
			SetupInfo->Release();
		}
	}
}

void cMainGame::Render()
{
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(g_hWnd, &ps);

	// 흰색으로 이미지를 칠한다.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (!isPause)
		g_pSceneManager->Render();
	else
		SetupInfo->Render();
	g_pTimeManager->Render();
	m_pImgBackBuffer->Render(hdc);

	EndPaint(g_hWnd, &ps);
}

void cMainGame::Release()
{
	g_pKeyManager->ReleaseInstance();
	g_pFileData->ReleaseInstance();
	g_pPixelManager->ReleaseInstance();
	g_pTimeManager->ReleaseInstance();
	g_pIniData->ReleaseInstance();
	g_pImageManager->ReleaseInstance();
	g_pSceneManager->ReleaseInstance();
	g_pSoundManager->ReleaseInstance();
}
