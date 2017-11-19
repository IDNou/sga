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

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_MARIO)
	{
		for (int i = 100; i < 200; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}

		/* 전체 배경 */
		m_pLoading->LoadImageFile("Map", "images/marioBackground.bmp", 8000, 600, true, RGB(255, 0, 255));
		

		/* 맵 */
		m_pLoading->LoadImageFile("Map_Magenta", "images/marioBackground_magenta.bmp", 8000, 600, true, RGB(255, 0, 255));

		g_pImageManager->AddEmptyImage("MapBuffer", WINSIZEX, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

		/* 미니맵 */

		/* 프로그레스바 */
		m_pLoading->LoadImageFile("HpBarBack", "images/progressBarBack.bmp", 50, 10);
		m_pLoading->LoadImageFile("HpBarFront", "images/progressBarFront.bmp", 50, 10);

		/* 지형물 오브젝트*/
		m_pLoading->LoadImageFile("fill", "images/fill.bmp", 193, 134, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("magenta", "images/magenta.bmp", 157, 149, true, RGB(0, 0, 0));
		m_pLoading->LoadFrameImage("bar", "images/MoveBar.bmp", 137, 20, 1, 1, 10, 150, true, RGB(255, 0, 255));

		/* 플레이어 */
		m_pLoading->LoadFrameImage("MarioRight", "images/mario_right.bmp", 262, 40, 4, 1, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("MarioRight2", "images/mario_right.bmp", 262, 80, 4, 1, true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("MarioLeft", "images/mario_left.bmp", 105, 30, 4, 1, true, RGB(255, 0, 255));

		/* 몬스터 */
		m_pLoading->LoadFrameImage("MushRoom", "images/mushroom.bmp", 75, 60, 2, 1, true, RGB(255, 0, 255));
		m_pLoading->LoadImageFile("Flower", "images/flower.bmp", 32, 45, true, RGB(255, 0, 255));

		/* 아이템 */
		m_pLoading->LoadImageFile("ItemMushRoom", "images/itemMushRoom.bmp", 37, 40, true, RGB(255, 0, 255));
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_FOTRESS)
	{
		for (int i = 200; i < 300; ++i)
		{
			str = itoa(i, szBuf, 10);

			m_pLoading->LoadEmpty(str, WINSIZEX, WINSIZEY);
		}

		/* 전체 배경 */

		/* 맵 */
		m_pLoading->LoadImageFile("Map", "images/fortressMagenta.bmp", 2814, 1500);

		/* 미니맵(빈 비트맵) - 원본 맵 사이즈의 1/5 사이즈로 만든다. */

		/* 프로그레스바 */
		m_pLoading->LoadImageFile("ProgressBack", "images/progressBarBack.bmp", 50, 10);
		m_pLoading->LoadImageFile("ProgressFront", "images/progressBarFront.bmp", 50, 10);

		/* 플레이어 */
		m_pLoading->LoadFrameImage("Player", "images/tank_cannon.bmp", 120, 60, 2, 1, 2000, (WINSIZEY - 110), true, RGB(255, 0, 255));
		m_pLoading->LoadFrameImage("Player2", "images/tank_carrottank.bmp", 120, 60, 2, 1, 800, 400, true, RGB(255, 0, 255));

		/* 폭탄 */
		m_pLoading->LoadFrameImage("Bomb", "images/bomb.bmp", 156, 39, 4, 1, true, RGB(255, 0, 255));
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_2048)
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

		m_pLoading->LoadImageFile("2", "images/2.bmp", 100, 100);
		m_pLoading->LoadImageFile("4", "images/4.bmp", 100, 100);
		m_pLoading->LoadImageFile("16", "images/16.bmp", 100, 100);
		m_pLoading->LoadImageFile("32", "images/32.bmp", 100, 100);
		m_pLoading->LoadImageFile("8", "images/8.bmp", 100, 100);
		m_pLoading->LoadImageFile("64", "images/64.bmp", 100, 100);
		m_pLoading->LoadImageFile("128", "images/128.bmp", 100, 100);
		m_pLoading->LoadImageFile("256", "images/256.bmp", 100, 100);
		m_pLoading->LoadImageFile("512", "images/512.bmp", 100, 100);
		m_pLoading->LoadImageFile("1024", "images/1024.bmp", 100, 100);
		m_pLoading->LoadImageFile("2048", "images/2048.bmp", 100, 100);
		m_pLoading->LoadFrameImage("Number", "images/numbers.bmp", 1100, 100, 11, 1, true, RGB(255, 0, 255));
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
	else if (g_pSceneManager->GetNextScene() == SLIST_MARIO)
	{
		
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_FOTRESS)
	{
	
	}
	else if (g_pSceneManager->GetNextScene() == SLIST_2048)
	{
	
	}
}
