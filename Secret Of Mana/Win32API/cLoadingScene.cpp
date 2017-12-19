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
	g_pImageManager->ReleaseImage("TitleBG");
	g_pImageManager->ReleaseImage("Start");
	g_pImageManager->ReleaseImage("StartVillage");
	g_pImageManager->ReleaseImage("StartVillage_Magenta");
	g_pImageManager->ReleaseImage("PlayerMoveAction");
	g_pImageManager->ReleaseImage("PlayerAttackAction");
	g_pImageManager->ReleaseImage("EmptyBuffer");
	g_pSoundManager->ReleaseSound("TitleSound");
	g_pSoundManager->ReleaseSound("FieldSound");
	/* ====================== */

	// 게임 전체에서 필요한 리소스는 타이틀 씬 로딩에서 전부 로드한다.
	switch (g_pSceneManager->GetNextScene())
	{
	case SLIST_TITLE:
		m_pLoading->LoadImageFile("TitleBG", "images/TitleBG.bmp", 1080, 720, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("Start", "images/start.bmp", 229, 50, true, RGB(255, 255, 255));
		break;
	case SLIST_PLAY:
		m_pLoading->LoadImageFile("StartVillage", "images/StartVillage.bmp", 1600, 1456);
		m_pLoading->LoadImageFile("StartVillage_Magenta", "images/StartVillage_Magenta.bmp", 1600, 1456, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("PlayerMoveAction", "images/MoveMotion.png", 280, 160, 7, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("PlayerAttackAction", "images/AttackMotion.png", 200, 160, 5, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("Rabit", "images/monster01.png", 200, 80, 5, 2, true, RGB(255, 0, 255));
		m_pLoading->LoadEmpty("EmptyBuffer", 1600, 1456);
		break;
	case SLIST_WATERPATH:
		m_pLoading->LoadImageFile("WaterAndPandoraPath", "images/WaterAndPandoraPath.png", 1120, 1664, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("WaterAndPandoraPath_Magenta", "images/WaterAndPandoraPath_Magenta.png", 1120, 1664, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("PlayerMoveAction", "images/MoveMotion.png", 280, 160, 7, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("PlayerAttackAction", "images/AttackMotion.png", 200, 160, 5, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("Rabit", "images/monster01.png", 200, 80, 5, 2, true, RGB(255, 0, 255));
		m_pLoading->LoadEmpty("EmptyBuffer", 1600, 1456);
		break;
	case SLIST_HOUSE:
		m_pLoading->LoadImageFile("House", "images/house.png", 705, 432, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("House_Magenta", "images/house_Magenta.png", 705, 432, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("PlayerMoveAction", "images/MoveMotion.png", 280, 160, 7, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("PlayerAttackAction", "images/AttackMotion.png", 200, 160, 5, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadEmpty("EmptyBuffer", 1600, 1456);
		break;
	}
}

void cLoadingScene::LoadingSound()
{
	switch (g_pSceneManager->GetNextScene())
	{
	case SLIST_TITLE:
		m_pLoading->LoadSound("TitleSound", "sounds/TitleSound.mp3", true, true);
		break;
	case SLIST_PLAY:
		m_pLoading->LoadSound("FieldSound", "sounds/FieldSound.mp3", true, true);
		break;
	case SLIST_WATERPATH:
		m_pLoading->LoadSound("WaterPath", "sounds/WaterPath.mp3", true, true);
		break;
	}
}