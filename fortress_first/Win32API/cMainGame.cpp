#include "stdafx.h"
#include "cMainGame.h"
#include "cMap.h"
#include "cPlayer.h"


cMainGame::cMainGame()
	: m_isPlaying(false)
{
	LoadImageFromFile();

	m_pMap = new cMap;
	m_pPlayer = new cPlayer;
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void cMainGame::Setup()
{
	m_pMap->Setup();
	m_pPlayer->Setup();
	m_pPlayer->SetMap(m_pMap);
}

void cMainGame::Update()
{
	cGameNode::Update();

	if (m_isPlaying)
	{
		m_pMap->Update();
		m_pPlayer->Update();
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		Setup();
		m_isPlaying = true;
	}
}

void cMainGame::Render()
{
	// 흰색으로 이미지를 칠한다.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
		m_pMap->Render();
		MiniMapRender();
		m_pPlayer->Render();
	}
	else
	{
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
	}
}

void cMainGame::LoadImageFromFile()
{
	/* 전체 배경 */
	g_pImageManager->AddImage("Map", "images/marioBackground.bmp", 8167, 600, true, RGB(255, 0, 255));

	/* 맵 */
	g_pImageManager->AddImage("Map_Magenta", "images/marioBackground_magenta.bmp", 8167, 600, true, RGB(255, 0, 255));

	g_pImageManager->AddImage("MapBuffer", WINSIZEX, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

	/* 미니맵 */
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", WINSIZEX, WINSIZEY / 5);

	/* 프로그레스바 */
	g_pImageManager->AddImage("HpBarBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("HpBarFront", "images/progressBarFront.bmp", 50, 10);

	/* 지형물 오브젝트*/

	/* 플레이어 */
	g_pImageManager->AddImage("Player", "images/ch.bmp", 960, 960, 12, 12,
		200, MAP1_Y, true, RGB(255, 0, 255));

	/* 몬스터 */
}

void cMainGame::MiniMapRender()
{
	m_pBufferMinimap = g_pImageManager->FindImage("Map");
	m_pImgBackgoround = g_pImageManager->FindImage("Map");
	m_pPlayer->MiniRender();
	
	//PatBlt(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5, BLACKNESS);
	m_pImgBackgoround->Render(m_pImgMiniMap->GetMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgBackgoround->GetFrameHeight());
	m_pBufferMinimap->AlphaRender(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5, 64);
	m_backBuffer->Render(m_pImgMiniMap->GetMemDC(), m_pMap->GetMoveX(), 0, WINSIZEX/5, WINSIZEY / 5);
	m_pImgMiniMap->Render(g_hDC, 0, 0);
}