#include "stdafx.h"
#include "cJumakScene.h"


cJumakScene::cJumakScene()
{
}


cJumakScene::~cJumakScene()
{
}

void cJumakScene::Setup()
{
	for (int y = 0; y < MaxY; y++)
	{
		for (int x = 0; x < MaxX; x++)
		{
			JumakTile[x][y] = m_pJumakTile->CreateDefaultTiles(x, y);
		}
	}


	m_pPlayBuffer = g_pImageManager->FindImage("PlayBuffer");
	m_nPosX = 420;
	m_nPosY = 700;
	//CreateDefaultTiles(40, 30);
	//// 왼쪽 ㄴㄴ
	//SettingTilesNoLeft(1, 1, 9, 15);
	//SettingTilesNoLeft(10, 10, 5, 8);
	//SettingTilesNoLeft(9, 9, 15, 18);
	//SettingTilesNoLeft(18, 18, 5, 7);
	//SettingTilesNoLeft(25, 25, 5, 7);
	//SettingTilesNoLeft(26, 26, 15, 24);
	//// 위쪽 ㄴㄴ
	//SettingTilesNoUp(1, 9, 9, 9);
	//SettingTilesNoUp(10, 35, 5, 5);
	//SettingTilesNoUp(15, 17, 8, 8);
	//SettingTilesNoUp(21, 24, 8, 8);
	//SettingTilesNoUp(33, 38, 8, 8);
	//// 오른쪽 ㄴㄴ
	//SettingTilesNoRight(11, 11, 15, 18);
	//SettingTilesNoRight(14, 14, 5, 7);
	//SettingTilesNoRight(20, 20, 5, 7);
	//SettingTilesNoRight(32, 32, 5, 7);
	//SettingTilesNoRight(38, 38, 8, 24);
	//
	//// 아래쪽 ㄴㄴ
	//SettingTilesNoDown(1, 8, 14, 14);
	//SettingTilesNoDown(9, 11, 18, 18);
	//SettingTilesNoDown(12, 25, 14, 14);
	//SettingTilesNoDown(26, 38, 24, 24);

	m_nMoveDelay = 0;
}


void cJumakScene::Update()
{
	RECT rt;
	m_rtPlayer = RectMakeCenter(m_nPosX, m_nPosY, 40, 40);

	m_rtViewPort = ViewPortMake(m_nPosX, m_nPosY, WINSIZEX - 200, WINSIZEY, 1600, 1200);

	//for (int a = 0; a < 30; a++)
	//{
	//	for (int b = 0; b < 40; b++)
	//	{
	//		if (IntersectRect(&rt, &m_rtPlayer, &JumakTile[b][a].rtTile)) // 타일 과 플레이어가 충돌 시
	//		{
	//			if (g_pKeyManager->isStayKeyDown(VK_LEFT) && JumakTile[b][a].isMoveLeft) // 타일의 LEFT값이 true이면
	//			{
	//				if(m_nMoveDelay ==0)
	//					m_nPosX -= 40;
	//				m_nMoveDelay++;
	//				if (m_nMoveDelay >= DELAY)
	//					m_nMoveDelay = 0;
	//			}
	//			else if (g_pKeyManager->isStayKeyDown(VK_RIGHT) && JumakTile[b][a].isMoveRight) // 타일의 RIGHT값이 true이면
	//			{
	//				if (m_nMoveDelay == 0)
	//					m_nPosX += 40;
	//				m_nMoveDelay++;
	//				if (m_nMoveDelay >= DELAY)
	//					m_nMoveDelay = 0;
	//			}
	//			else if (g_pKeyManager->isStayKeyDown(VK_UP) && JumakTile[b][a].isMoveUp) // 타일의 UP값이 true이면
	//			{
	//				if (m_nMoveDelay == 0)
	//					m_nPosY -= 40;
	//				m_nMoveDelay++;
	//				if (m_nMoveDelay >= DELAY)
	//					m_nMoveDelay = 0;
	//			}
	//			else if (g_pKeyManager->isStayKeyDown(VK_DOWN) && JumakTile[b][a].isMoveDown) // 타일의 DOWN값이 true이면
	//			{
	//				if (m_nMoveDelay == 0)
	//					m_nPosY += 40;
	//				m_nMoveDelay++;
	//				if (m_nMoveDelay >= DELAY)
	//					m_nMoveDelay = 0;
	//			}
	//		
	//		}
	//		if (PtInRect(&JumakTile[b][a].rtTile, g_ptMouse))
	//		{
	//			cout << JumakTile[b][a].nCoorX << " " << JumakTile[b][a].nCoorY << endl; // 이상함?
	//			//cout <<" " << JumakTile[b][a].isMoveRight << " " << JumakTile[b][a].isMoveDown << " " << endl;
	//		}
	//	}
	//}
	
}

void cJumakScene::Render()
{
		
	g_pImageManager->Render("Jumak", m_pPlayBuffer->GetMemDC());
	RectangleMake(m_pPlayBuffer->GetMemDC(), m_rtPlayer);
	m_pPlayBuffer->ViewPortRender(g_hDC, m_rtViewPort, WINSIZEX-200, WINSIZEY);
	//RectangleRender(40, 30);
}

void cJumakScene::Release()
{
}

