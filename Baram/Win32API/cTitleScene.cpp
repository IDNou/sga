#include "stdafx.h"
#include "cTitleScene.h"


void cTitleScene::Setup()
{
	g_pSoundManager->Play("Main_BGM", 1.0f);
	m_MainImage = g_pImageManager->FindImage("Main");
	m_CursorImage = g_pImageManager->FindImage("Cursor");
	m_CharacterScreen = g_pImageManager->FindImage("CharacterScreen");
	m_Select = g_pImageManager->FindImage("Select");

	rt_Start = RectMake(WINSIZEX - 274, 435, 240, 25);
	rt_Load = RectMake(WINSIZEX - 274, 510, 240, 25);
	rt_Staff = RectMake(WINSIZEX - 274, 593, 240, 25);
	rt_Exit = RectMake(WINSIZEX - 274, 676, 240, 25);

	rt_SelectCharacter1 = RectMake(WINSIZEX - 0, 0, 0, 0);
	rt_SelectCharacter2 = RectMake(WINSIZEX - 0, 0, 0, 0);
	rt_SelectCharacter3 = RectMake(WINSIZEX - 0, 0, 0, 0);
	rt_SelectDone = RectMake(WINSIZEX - 0, 0, 0, 0);
	rt_SelectCancel = RectMake(WINSIZEX - 0, 0, 0, 0);

	m_isCharacterScreen = false;
	m_isCharacter1 = false;
	m_isCharacter2 = false;
	m_isCharacter3 = false;
}

void cTitleScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		g_pSceneManager->SetNextScene(SLIST_DUNGEON1);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
	//메인화면씬에서 클릭으로 다른씬 넘어가기
	if (PtInRect(&rt_Start, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		//m_isCharacterScreen = true;



		g_pSceneManager->SetNextScene(SLIST_PLAY);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (PtInRect(&rt_Load, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		g_pSceneManager->SetNextScene(SLIST_LOAD);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (PtInRect(&rt_Staff, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		g_pSceneManager->SetNextScene(SLIST_STAFF);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (PtInRect(&rt_Exit, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		PostQuitMessage(0); //종료명령어
	}

	//클릭 사운드 테스트
	if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON)) { g_pSoundManager->Play("Click_SD", 1.0f); }
}

void cTitleScene::Render()
{
	m_MainImage->Render(g_hDC, 0, 0, WINSIZEX, WINSIZEY);

	if (m_isCharacterScreen)
	{
		m_CharacterScreen->Render(g_hDC, 0, 0, WINSIZEX, WINSIZEY);
		m_Select->Render(g_hDC, 0, 0);
	}


	//충돌처리 렉트 랜더
	//RectangleMake(g_hDC, rt_Start);
	//RectangleMake(g_hDC, rt_Load);
	//RectangleMake(g_hDC, rt_Staff);
	//RectangleMake(g_hDC, rt_Exit);

	RectangleMake(g_hDC, rt_SelectCharacter1);
	RectangleMake(g_hDC, rt_SelectCharacter2);
	RectangleMake(g_hDC, rt_SelectCharacter3);
	RectangleMake(g_hDC, rt_SelectDone);
	RectangleMake(g_hDC, rt_SelectCancel);

	m_CursorImage->FrameRender(g_hDC, g_ptMouse.x, g_ptMouse.y, 0, 0, 7, 0, 5);
}

void cTitleScene::Release()
{
	
}
