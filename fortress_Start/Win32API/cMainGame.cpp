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

	m_pMap->SetPlayer(m_pPlayer);
	m_pPlayer->SetMap(m_pMap);
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
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(g_hWnd, &ps);

	// 흰색으로 이미지를 칠한다.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
		m_pMap->Render();
		m_pPlayer->Render();
		m_pImgMapBuffer->Render(g_hDC, 0, 0, m_pPlayer->GetPosX() - WINSIZEX / 2, m_pPlayer->GetPosY() - WINSIZEY / 2, WINSIZEX, WINSIZEY);

	//	MiniMapRender();
	}
	else
	{
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
	}

	g_pTimeManager->Render();
	m_pImgBackBuffer->Render(hdc);

	EndPaint(g_hWnd, &ps);
}

void cMainGame::LoadImageFromFile()
{
	/* 전체 배경 */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/fortressBackGround.bmp", 3753, 2000);

	/* 맵 */
	g_pImageManager->AddImage("Map", "images/fortressMagenta.bmp", 3753, 2000);
	m_pImgMapBuffer = g_pImageManager->AddImage("MapBuffer", 3753, 2000);
	m_pImgMapBuffer->SetTransColor(true, RGB(255, 0, 255));

	/* 미니맵(빈 비트맵) - 원본 맵 사이즈의 1/5 사이즈로 만든다. */ 
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", 3753 / 5, 2000 / 5);

	/* 프로그레스바 */
	g_pImageManager->AddImage("ProgressBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("ProgressFront", "images/progressBarFront.bmp", 50, 10);

	/* 플레이어 */
	g_pImageManager->AddImage("Player", "images/tank_cannonRight.bmp", 60, 60, 1, 1, 1500, MAP1_Y, true, RGB(255, 0, 255));
}

void cMainGame::MiniMapRender()
{
	/* 모든 것들을 미니맵 사이즈로 축소해서 그린다. */

	// 배경을 먼저 그린다.
	m_pImgBackground->Render(m_pImgMiniMap->GetMemDC(), 0, 0,
		m_pImgMiniMap->GetWidth(), m_pImgMiniMap->GetHeight());

	// 지형 지물을 그린다.
	m_pImgMapBuffer->Render(m_pImgMiniMap->GetMemDC(), 0, 0,
		m_pImgMiniMap->GetWidth(), m_pImgMiniMap->GetHeight());

	// 플레이어 위치
	/*RectangleMakeCenter(m_pImgMiniMap->GetMemDC(),
		(m_pPlayer->GetPosX() + m_pMap->GetPosX()) / 5,
		(m_pPlayer->GetPosY() + m_pMap->GetPosY()) / 5,
		m_pPlayer->GetSizeX() / 5, m_pPlayer->GetSizeY() / 5);*/

	m_pImgMiniMap->Render(g_hDC, 0, 0, WINSIZEX, WINSIZEY / 5);
}
