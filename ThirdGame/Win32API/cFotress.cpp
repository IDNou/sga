#include "stdafx.h"
#include "cFotress.h"
#include "cFotressMap.h"
#include "cFotressPlayer.h"

void cFotress::Setup()
{
	m_isPlaying = false;
	LoadImageFromFile();

	m_pMap = new cFotressMap;
	m_pPlayer = new cFotressPlayer;

	m_pMap->SetPlayer(m_pPlayer);
	m_pPlayer->SetMap(m_pMap);

	m_pMap->Setup();
	m_pPlayer->Setup();
	PosX = 0;
	PosY = 0;
	savePosX = 0;
	savePosY = 0;
}

void cFotress::Update()
{
	if (m_isPlaying)
	{
		m_pMap->Update();
		m_pPlayer->Update();

		if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
			m_isPlaying = false;

		switch (m_pPlayer->GetPlayerTurn())
		{
		case FirstPlayer:
			if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 > 0
				&& m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 < m_pImgMapBuffer->GetWidth())
				PosX = m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX();
			else if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 < 0)
				PosX = WINSIZEX / 2;
			else if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 > m_pImgMapBuffer->GetWidth())
				PosX = m_pImgMapBuffer->GetWidth() - WINSIZEX / 2;

			if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 > 0
				&& m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 < m_pImgMapBuffer->GetHeight())
				PosY = m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY();
			else if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 < 0)
				PosY = WINSIZEY / 2;
			else if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 > m_pImgMapBuffer->GetHeight())
				PosY = m_pImgMapBuffer->GetHeight() - WINSIZEY / 2;
			break;

		case SecondPlayer:
			if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 > 0
				&& m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 < m_pImgMapBuffer->GetWidth())
				PosX = m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX();
			else if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 < 0)
				PosX = WINSIZEX / 2;
			else if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 > m_pImgMapBuffer->GetWidth())
				PosX = m_pImgMapBuffer->GetWidth() - WINSIZEX / 2;

			if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 > 0
				&& m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 < m_pImgMapBuffer->GetHeight())
				PosY = m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY();
			else if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 < 0)
				PosY = WINSIZEY / 2;
			else if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 > m_pImgMapBuffer->GetHeight())
				PosY = m_pImgMapBuffer->GetHeight() - WINSIZEY / 2;
			break;
		default:
			break;
		}

		if (g_pKeyManager->isStayKeyDown('D') && PosX + savePosX + WINSIZEX / 2 < m_pImgMapBuffer->GetWidth() - 3)
		{
			savePosX += 3;
		}
		if (g_pKeyManager->isOnceKeyUp('D'))
		{
			savePosX = 0;
		}
		if (g_pKeyManager->isStayKeyDown('A'))
		{
			if (PosX + savePosX - WINSIZEX / 2 > 3)
				savePosX -= 3;
		}
		if (g_pKeyManager->isOnceKeyUp('A'))
		{
			savePosX = 0;
		}
		if (g_pKeyManager->isStayKeyDown('W'))
		{
			if (PosY + savePosY - WINSIZEY / 2 > 3)
				savePosY -= 3;
		}
		if (g_pKeyManager->isOnceKeyUp('W'))
		{
			savePosY = 0;
		}
		if (g_pKeyManager->isStayKeyDown('S'))
		{
			if (PosY + savePosY + WINSIZEY / 2 < m_pImgMapBuffer->GetHeight() - 3)
				savePosY += 3;
		}
		if (g_pKeyManager->isOnceKeyUp('S'))
		{
			savePosY = 0;
		}

	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		Setup();
		m_isPlaying = true;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
}

void cFotress::Render()
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
		m_pImgMapBuffer->Render(g_hDC, 0, 0, PosX + savePosX - WINSIZEX / 2, PosY + savePosY - WINSIZEY / 2, WINSIZEX, WINSIZEY);

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

void cFotress::Release()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void cFotress::LoadImageFromFile()
{
	/* 전체 배경 */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/fortressBackGround.bmp", 2814, 1500);

	/* 맵 */
	m_pImgMapBuffer = g_pImageManager->AddEmptyImage("MapBuffer", 2814, 1500);
	m_pImgMapBuffer->SetTransColor(true, RGB(255, 0, 255));

	/* 미니맵(빈 비트맵) - 원본 맵 사이즈의 1/5 사이즈로 만든다. */
	m_pImgMiniMap = g_pImageManager->AddEmptyImage("MiniMap", 2814 / 5, 1500 / 5);

}

void cFotress::MiniMapRender()
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

	m_pImgMiniMap->Render(g_hDC, WINSIZEX - WINSIZEX / 5, 0, WINSIZEX / 5, WINSIZEY / 5);
}
