#include "stdafx.h"
#include "cMainGame.h"

// 씬 헤더파일들 추가
#include "cTitleScene.h"
#include "cPlayScene.h"
#include "cLoadingScene.h"
#include "cDungeon1.h"
#include "cDungeon2.h"
#include "cDungeon3.h"
#include "cDungeon4.h"

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
	g_pSceneManager->AddScene(SLIST_PLAY, new cPlayScene);
	g_pSceneManager->AddScene(SLIST_DUNGEON1, new cDungeon1);
	g_pSceneManager->AddScene(SLIST_DUNGEON2, new cDungeon2);
	g_pSceneManager->AddScene(SLIST_DUNGEON3, new cDungeon3);
	g_pSceneManager->AddScene(SLIST_DUNGEON4, new cDungeon4);

	// 처음 게임플레이어 스탯설정
	g_pIniData->AddData("stat", "HP", "100");
	g_pIniData->AddData("stat", "Money", "0");
	g_pIniData->AddData("stat", "ATK", "10");
	g_pIniData->AddData("stat", "DEF", "10");
	g_pIniData->AddData("stat", "Kit", "0");
	g_pIniData->AddData("stat", "MaNaKit", "0");
	g_pIniData->IniSave("charater.ini");


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
