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
	g_pImageManager->ReleaseImage("Rabit");
	g_pImageManager->ReleaseImage("WaterAndPandoraPath");
	g_pImageManager->ReleaseImage("WaterAndPandoraPath_Magenta");
	g_pImageManager->ReleaseImage("House");
	g_pImageManager->ReleaseImage("House_Magenta");
	g_pImageManager->ReleaseImage("Store_Empty");
	g_pImageManager->ReleaseImage("CommunicationBox");
	g_pImageManager->ReleaseImage("Finger2");
	g_pImageManager->ReleaseImage("StoreNPC");
	g_pImageManager->ReleaseImage("BossMap");
	g_pImageManager->ReleaseImage("BossMap_Magenta");
	g_pSoundManager->ReleaseSound("TitleSound");
	g_pSoundManager->ReleaseSound("FieldSound");
	g_pSoundManager->ReleaseSound("WaterPath");
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
		m_pLoading->LoadFrameImage("CommunicationBox", "images/CommunicationBox.png", 45, 45, 3, 3, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("Rabit", "images/monster01.png", 200, 160, 5, 4, true, RGB(255, 0, 255));
		m_pLoading->LoadEmpty("EmptyBuffer", 1600, 1456);
		break;
	case SLIST_WATERPATH:
		m_pLoading->LoadImageFile("WaterAndPandoraPath", "images/WaterAndPandoraPath.png", 1120, 1664, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("WaterAndPandoraPath_Magenta", "images/WaterAndPandoraPath_Magenta.png", 1120, 1664, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("PlayerMoveAction", "images/MoveMotion.png", 280, 160, 7, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("PlayerAttackAction", "images/AttackMotion.png", 200, 160, 5, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("CommunicationBox", "images/CommunicationBox.png", 45, 45, 3, 3, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("Rabit", "images/monster01.png", 200, 160, 5, 4, true, RGB(255, 0, 255));
		m_pLoading->LoadEmpty("EmptyBuffer", 1120, 1664);
		break;
	case SLIST_HOUSE:
		m_pLoading->LoadImageFile("House", "images/house.png", 705, 432, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("House_Magenta", "images/house_Magenta.png", 705, 432, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("PlayerMoveAction", "images/MoveMotion.png", 280, 160, 7, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("PlayerAttackAction", "images/AttackMotion.png", 200, 160, 5, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("StoreNPC", "images/StoreNPC.png", 120, 45, 4, 1, true, RGB(255, 0, 255));
		m_pLoading->LoadEmpty("Store_Empty", WINSIZEX / 2, WINSIZEY / 2);
		m_pLoading->LoadFrameImage("CommunicationBox", "images/CommunicationBox.png", 45, 45, 3, 3, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("Finger2", "images/Finger.png", 16, 16, true, RGB(255, 0, 255));
		m_pLoading->LoadEmpty("EmptyBuffer", 705, 432);
		break;
	case SLIST_BOSSMAP:
		m_pLoading->LoadImageFile("BossMap", "images/BossMap.png", 540, 360, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("BossMap_Magenta", "images/BossMap_Magenta.png", 540, 360, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("PlayerMoveAction", "images/MoveMotion.png", 280, 160, 7, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("PlayerAttackAction", "images/AttackMotion.png", 200, 160, 5, 4, true, RGB(0, 128, 0));
		m_pLoading->LoadFrameImage("CommunicationBox", "images/CommunicationBox.png", 45, 45, 3, 3, true, RGB(255, 0, 255));
		m_pLoading->LoadEmpty("EmptyBuffer", 540, 360);
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
	case SLIST_BOSSMAP:
		break;
	}
}