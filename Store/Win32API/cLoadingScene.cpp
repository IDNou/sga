#include "stdafx.h"
#include "cLoadingScene.h"


void cLoadingScene::Setup()
{
	m_pLoading = new cLoading;
	m_pLoading->Setup();

	LoadingImage();
	LoadingSound();
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
	/* ====================== */

	// 게임 전체에서 필요한 리소스는 타이틀 씬 로딩에서 전부 로드한다.
	if (g_pSceneManager->GetNextScene() == SLIST_TITLE)
	{
		for (int i = 0; i < 100; ++i)
		{
			str = itoa(i, szBuf, 10);

			if (i == 0)
			{
				m_pLoading->LoadImageFile(str, "images/Dungeon1.bmp",100,100,true,RGB(255,0,255));
			}
			else if (i == 1)
			{
				m_pLoading->LoadImageFile(str, "images/Dungeon2.bmp", 100, 100, true, RGB(255, 0, 255));
			}
			else if (i == 2) 
			{
				m_pLoading->LoadImageFile(str, "images/store1.bmp", 100, 100, true, RGB(255, 0, 255));
			}
			else if (i == 3)
			{
				m_pLoading->LoadImageFile(str, "images/store2.bmp", 100, 100, true, RGB(255, 0, 255));
			}
			else if (i == 4)
			{
				m_pLoading->LoadFrameImage(str, "images/human.bmp", 100, 100, 1, 1, WINSIZEX / 2 - 150, WINSIZEY / 2 - 50, true, RGB(255, 0, 255));
			}
			else
				m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_DUNGEON1)
	{
		for (int i = 100; i < 200; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_DUNGEON2)
	{
		for (int i = 200; i < 300; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_DUNGEON3)
	{
		for (int i = 300; i < 400; ++i)
		{
			str = itoa(i, szBuf, 10);

			if (i == 300)
			{
				m_pLoading->LoadFrameImage(str, "images/human.bmp", 100, 100, 1, 1, WINSIZEX / 2 - 150, WINSIZEY / 2 - 50, true, RGB(255, 0, 255));
			}
			else
				m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_DUNGEON4)
	{
		for (int i = 400; i < 500; ++i)
		{
			str = itoa(i, szBuf, 10);

			if (i == 400)
			{
				m_pLoading->LoadFrameImage(str, "images/human.bmp", 100, 100, 1, 1, WINSIZEX / 2 - 150, WINSIZEY / 2 - 50, true, RGB(255, 0, 255));
			}
			else
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
		m_pLoading->LoadSound("buyeu", "sounds/buyeu.mp3", true, true);
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_DUNGEON1)
	{
		m_pLoading->LoadSound("buyeu", "sounds/buyeu.mp3", true, true);
		m_pLoading->LoadSound("coin", "sounds/coin.wav", false, false);
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_DUNGEON2)
	{
		m_pLoading->LoadSound("buyeu", "sounds/buyeu.mp3", true, true);
		m_pLoading->LoadSound("coin", "sounds/coin.wav", false, false);
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_DUNGEON3)
	{
		m_pLoading->LoadSound("dungeon1", "sounds/dungeon1.mp3", true, true);
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_DUNGEON4)
	{
		m_pLoading->LoadSound("dungeon2", "sounds/dungeon2.mp3", true, true);
	}
}
