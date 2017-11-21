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
	// m_pLoading->LoadingDone() : ���� ���� ���ҽ� �ε��� ���α׷����� ������Ʈ
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

	/* ==== ���ҽ� ���� ===== */
	for (int i = 100; i < 500; ++i)
	{
		str = itoa(i, szBuf, 10);
		g_pImageManager->ReleaseImage(str);
	}
	g_pImageManager->ReleaseImage("Player");

	/*========�������� ������*/
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

	// ���� ��ü���� �ʿ��� ���ҽ��� Ÿ��Ʋ �� �ε����� ���� �ε��Ѵ�.
	if (g_pSceneManager->GetNextScene() == SLIST_TITLE)
	{
		for (int i = 0; i < 100; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
		m_pLoading->LoadFrameImage("Player", "images/Player.bmp", 160, 200, 4, 4, true, RGB(224, 219, 220));
		m_pLoading->LoadImageFile("Main", "images/����.bmp", WINSIZEX, WINSIZEY);
		m_pLoading->LoadImageFile("CharacterScreen", "images/����â.bmp", WINSIZEX, WINSIZEY);
		m_pLoading->LoadFrameImage("Cursor", "images/���콺.bmp", 160, 24, 8, 1, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("Select", "images/����â����.bmp", 135, 250, true, RGB(255, 0, 255));

	}
	else if (g_pSceneManager->GetNextScene() == SLIST_PLAY)
	{
		m_pLoading->LoadFrameImage("Cursor", "images/���콺.bmp", 160, 24, 8, 1, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("Mainframe", "images/ȭ��Ʋ.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainState", "images/���â.bmp", 214, 555, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("State1", "images/�ɷ�ġ1.bmp", 252, 291, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("State2", "images/�ɷ�ġ2.bmp", 252, 291, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainItem", "images/������â.bmp", 214, 555, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainSkill", "images/��ųâ.bmp", 214, 555, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainLevel", "images/����ǥ��â.bmp", 216, 76, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("MainHP", "images/ü��ǥ��â.bmp", 207, 89, true, RGB(255, 0, 255));

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
	//������ ���ֱ�
	g_pSoundManager->ReleaseSound("Main_BGM");
	g_pSoundManager->ReleaseSound("Click_SD");

	//�� ���� ���� �ε����ֱ�
	switch (g_pSceneManager->GetNextScene())
	{
	case SLIST_TITLE:
		m_pLoading->LoadSound("Main_BGM", "sounds/����.mp3", true, true);
		m_pLoading->LoadSound("Click_SD", "sounds/Ŭ��.mp3");
		break;
	case SLIST_PLAY:
		m_pLoading->LoadSound("Click_SD", "sounds/Ŭ��.mp3");
		break;
	case SLIST_LOAD:
		break;
	case SLIST_STAFF:
		break;
	}
}
