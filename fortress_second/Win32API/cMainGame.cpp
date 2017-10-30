#include "stdafx.h"
#include "cMainGame.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cObjects.h"


cMainGame::cMainGame()
	: m_isPlaying(false)
{
	LoadImageFromFile();

	m_pMap = new cMap;
	m_pPlayer = new cPlayer;
	m_pObject = new cObjects;
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
	m_pPlayer->SetObject(m_pObject);
	m_pObject->Setup();
	m_pObject->SetPlayer(m_pPlayer);
	m_pObject->SetMap(m_pMap);
}

void cMainGame::Update()
{
	cGameNode::Update();

	if (m_isPlaying)
	{
		m_pMap->Update();
		m_pPlayer->Update();
		m_pObject->Update();

		if (m_pPlayer->GetIsDie())
			m_isPlaying = false;
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
		m_pObject->Render();
	}
	else
	{
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
	}
}

void cMainGame::LoadImageFromFile()
{
	/* 전체 배경 */
	g_pImageManager->AddImage("Map", "images/marioBackground.bmp", 8000, 600, true, RGB(255, 0, 255));

	/* 맵 */
	g_pImageManager->AddImage("Map_Magenta", "images/marioBackground_magenta.bmp", 8000, 600, true, RGB(255, 0, 255));

	g_pImageManager->AddImage("MapBuffer", WINSIZEX, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

	/* 미니맵 */
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", WINSIZEX, WINSIZEY / 5);

	/* 프로그레스바 */
	g_pImageManager->AddImage("HpBarBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("HpBarFront", "images/progressBarFront.bmp", 50, 10);

	/* 지형물 오브젝트*/
	g_pImageManager->AddImage("fill", "images/fill.bmp", 193, 134, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("magenta", "images/magenta.bmp", 157, 149, true, RGB(0, 0, 0));

	/* 플레이어 */
	g_pImageManager->AddImage("Player", "images/ch.bmp", 960, 960, 12, 12,
		200, MAP1_Y, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("MarioRight", "images/mario_right.bmp", 262, 40, 4, 1, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("MarioLeft", "images/mario_left.bmp", 105, 30, 4, 1, true, RGB(255, 0, 255));

	/* 몬스터 */
	g_pImageManager->AddImage("MushRoom", "images/mushroom.bmp", 75, 60, 2, 1, true, RGB(255, 0, 255));

}

void cMainGame::MiniMapRender()
{
	m_pBufferMinimap = g_pImageManager->FindImage("Map");
	m_pImgBackgoround = g_pImageManager->FindImage("Map");
	m_pPlayer->MiniRender();
	
	//PatBlt(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5, BLACKNESS);
	m_pImgBackgoround->Render(m_pImgMiniMap->GetMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgBackgoround->GetFrameHeight());
	m_pBufferMinimap->AlphaRender(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5, 64); // 알파 미니맵
	m_backBuffer->Render(m_pImgMiniMap->GetMemDC(), m_pMap->GetMoveX() / (m_pBufferMinimap->GetFrameWidth() / WINSIZEX), 0,
		WINSIZEX/(m_pBufferMinimap->GetFrameWidth() / WINSIZEX), WINSIZEY / 5); // 미니맵 추적기
	m_pImgMiniMap->Render(g_hDC, 0, 0);
}