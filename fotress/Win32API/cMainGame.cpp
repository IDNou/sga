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

	// ������� �̹����� ĥ�Ѵ�.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
		m_pImgBackground->Render(g_hDC, 0, 0, m_pMap->GetPosX(), m_pMap->GetPosY(), WINSIZEX, WINSIZEY);

		m_pMap->Render();
		m_pPlayer->Render();

		MiniMapRender();
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
	/* ��ü ��� */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/map_bg.bmp", 6600, 675);

	/* �� */
	g_pImageManager->AddImage("Map", "images/map_magenta.bmp", 6600, 675);
	m_pImgMapBuffer = g_pImageManager->AddImage("MapBuffer", 6600, 675);
	m_pImgMapBuffer->SetTransColor(true, RGB(255, 0, 255));

	/* �̴ϸ�(�� ��Ʈ��) - ���� �� �������� 1/5 ������� �����. */ 
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", 6600 / 5, 675 / 5);

	/* ���α׷����� */
	g_pImageManager->AddImage("ProgressBack", "images/progressBarBack.bmp", 50, 10);
	g_pImageManager->AddImage("ProgressFront", "images/progressBarFront.bmp", 50, 10);

	/* �÷��̾� */
	g_pImageManager->AddImage("Player", "images/ch.bmp", 960, 960, 12, 12, 200, MAP1_Y, true, RGB(255, 0, 255));
}

void cMainGame::MiniMapRender()
{
	/* ��� �͵��� �̴ϸ� ������� ����ؼ� �׸���. */

	// ����� ���� �׸���.
	m_pImgBackground->Render(m_pImgMiniMap->GetMemDC(), 0, 0,
		m_pImgMiniMap->GetWidth(), m_pImgMiniMap->GetHeight());

	// ���� ������ �׸���.
	m_pImgMapBuffer->Render(m_pImgMiniMap->GetMemDC(), 0, 0,
		m_pImgMiniMap->GetWidth(), m_pImgMiniMap->GetHeight());

	// �÷��̾� ��ġ
	RectangleMakeCenter(m_pImgMiniMap->GetMemDC(),
		(m_pPlayer->GetPosX() + m_pMap->GetPosX()) / 5,
		(m_pPlayer->GetPosY() + m_pMap->GetPosY()) / 5,
		m_pPlayer->GetSizeX() / 5, m_pPlayer->GetSizeY() / 5);

	m_pImgMiniMap->Render(g_hDC, 0, 0, WINSIZEX, WINSIZEY / 5);
}
