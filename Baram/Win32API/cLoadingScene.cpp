#include "stdafx.h"
#include "cLoadingScene.h"


void cLoadingScene::Setup()
{
	m_pLoading = new cLoading;
	m_pLoading->Setup();

	LoadingImage();
	LoadingSound();
	LoadingItem();
}

void cLoadingScene::Update()
{
	// m_pLoading->LoadingDone() : 실질 적인 리소스 로딩과 프로그레스바 업데이트
	if (m_pLoading->LoadingDone())
	{
		g_pSceneManager->ChangeScene(g_pSceneManager->GetNextScene());
	}
}

void cLoadingScene::Render()
{
	m_pLoading->Render();
}

void cLoadingScene::Release()
{
	SAFE_DELETE(m_pLoading);
}

void cLoadingScene::LoadingImage()
{
	char szBuf[32];
	char* str;

	/* ==== 리소스 해제 ===== */
	for (int i = 100; i < 500; ++i)
	{
		str = itoa(i, szBuf, 10);
		g_pImageManager->ReleaseImage(str);
	}
	g_pImageManager->ReleaseImage("Player");

	/*========승훈이형 릴리즈*/
	g_pImageManager->ReleaseImage("Main");
	g_pImageManager->ReleaseImage("Cursor");
	g_pImageManager->ReleaseImage("Mainframe");
	g_pImageManager->ReleaseImage("MainState");
	g_pImageManager->ReleaseImage("State1");
	g_pImageManager->ReleaseImage("State2");
	g_pImageManager->ReleaseImage("MainItem");
	g_pImageManager->ReleaseImage("MainSkill");
	g_pImageManager->ReleaseImage("MainLevel");
	g_pImageManager->ReleaseImage("MainHP");
	g_pImageManager->ReleaseImage("CharacterScreen");
	g_pImageManager->ReleaseImage("Select");

	/* ====================== */

	// 게임 전체에서 필요한 리소스는 타이틀 씬 로딩에서 전부 로드한다.
	if (g_pSceneManager->GetNextScene() == SLIST_TITLE)
	{
		for (int i = 0; i < 100; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
		m_pLoading->LoadFrameImage("Player", "images/Player.bmp", 160, 200, 4, 4, true, RGB(224, 219, 220));
		m_pLoading->LoadImageFile("Main", "images/메인.bmp", WINSIZEX, WINSIZEY);
		m_pLoading->LoadImageFile("CharacterScreen", "images/생성창.bmp", WINSIZEX, WINSIZEY);
		m_pLoading->LoadFrameImage("Cursor", "images/마우스.bmp", 160, 24, 8, 1, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("Select", "images/생성창선택.bmp", 135, 250, true, RGB(255, 0, 255));

	}
	else if (g_pSceneManager->GetNextScene() == SLIST_PLAY)
	{
		m_pLoading->LoadFrameImage("Cursor", "images/마우스.bmp", 160, 24, 8, 1, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("Mainframe", "images/화면틀.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainState", "images/장비창.bmp", 214, 555, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("State1", "images/능력치1.bmp", 252, 291, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("State2", "images/능력치2.bmp", 252, 291, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainItem", "images/아이템창.bmp", 214, 555, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainSkill", "images/스킬창.bmp", 214, 555, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainLevel", "images/레벨표시창.bmp", 216, 76, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainHP", "images/체력표시창.bmp", 207, 89, true, RGB(255, 0, 255));

		for (int i = 100; i < 200; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_LOAD)
	{
		for (int i = 200; i < 300; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_STAFF)
	{
		for (int i = 300; i < 400; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
}

void cLoadingScene::LoadingSound()
{
	char szBuf[32];
	char* str;

	//g_pSoundManager->AllReleaseSound();

	if (g_pSceneManager->GetNextScene() == SLIST_TITLE)
	{
		
	}
	
}

void cLoadingScene::LoadingItem()
{
	//릴리즈 해주기
	g_pSoundManager->ReleaseSound("Main_BGM");
	g_pSoundManager->ReleaseSound("Click_SD");

	//각 씬에 사운드 로딩해주기
	switch (g_pSceneManager->GetNextScene())
	{
	case SLIST_TITLE:
		m_pLoading->LoadSound("Main_BGM", "sounds/메인.mp3", true, true);
		m_pLoading->LoadSound("Click_SD", "sounds/클릭.mp3");
		break;
	case SLIST_PLAY:
		m_pLoading->LoadSound("Click_SD", "sounds/클릭.mp3");
		break;
	case SLIST_LOAD:
		break;
	case SLIST_STAFF:
		break;
	}
}
