#include "stdafx.h"
#include "cMainGame.h"

// 씬 헤더파일들 추가
#include "cTitleScene.h"
#include "cLoadingScene.h"
#include "cJumakScene.h"
#include "cVillageScene.h"
#include "cDungeon1.h"
#include "cPlay.h"
#include "cLoad.h"
#include "cStaff.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
}

void cMainGame::Setup()
{
	// 씬 추가
	g_pSceneManager->AddScene(SLIST_TITLE, new cTitleScene);
	g_pSceneManager->AddScene(SLIST_LOADING, new cLoadingScene);
	g_pSceneManager->AddScene(SLIST_JUMAK, new cJumakScene);
	g_pSceneManager->AddScene(SLIST_VILLAGE, new cVillageScene);
	g_pSceneManager->AddScene(SLIST_DUNGEON1, new cDungeon1);
	g_pSceneManager->AddScene(SLIST_PLAY, new cPlay);
	g_pSceneManager->AddScene(SLIST_LOAD, new cLoad);
	g_pSceneManager->AddScene(SLIST_STAFF, new cStaff);

	// 처음 시작 씬 셋팅
	g_pSceneManager->ChangeScene(SLIST_LOADING);
}

void cMainGame::Update()
{
	cGameNode::Update();

	g_pSceneManager->Update();
}

void cMainGame::Render()
{
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(g_hWnd, &ps);

	// 흰색으로 이미지를 칠한다.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	g_pSceneManager->Render();
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

	g_pImageManager->ReleaseAll();
	g_pImageManager->ReleaseInstance();
}
