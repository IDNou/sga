#include "stdafx.h"
#include "cDungeon1.h"


cDungeon1::cDungeon1()
{
}


cDungeon1::~cDungeon1()
{
}

void cDungeon1::Setup()
{
	LoadingImage();
	g_pImageManager->AddEmptyImage("PlayBuffer", 1080, 720);
	m_pPlayBuffer = g_pImageManager->FindImage("PlayBuffer");
	m_nPosX = 540;
	m_nPosY = 620;
	m_nMoveDelay = 0;
	Error = RectMakeCenter(220, 220, 40, 40);
	for (int y = 0; y < MaxY; y++)
	{
		for (int x = 0; x < MaxX; x++)
		{
			DungeonTile[x][y] = m_pDungeonTile->CreateDefaultTiles(x, y);
			DungeonTile[x][y].isMove = m_pDungeonTile->SettingTilesNoMove();
		}
	}
	for (int y = 1; y < 17; y++)
	{
		for (int x = 1; x < 26; x++)
		{
			DungeonTile[x][y].isMove = m_pDungeonTile->SettingTilesMove();
		}
	}
	for (int x = 11; x < 15; x++)
	{
		DungeonTile[x][17].isMove = m_pDungeonTile->SettingTilesMove();
	}
	DungeonTile[5][5].isMove = false;
}

void cDungeon1::Update()
{
	m_rtPlayer = RectMakeCenter(m_nPosX, m_nPosY,40,40);
	m_rtTop = RectMakeCenter(m_nPosX, m_nPosY -40, 40, 40);
	m_rtBottom = RectMakeCenter(m_nPosX, m_nPosY + 40, 40, 40);
	m_rtLeft = RectMakeCenter(m_nPosX -40 , m_nPosY, 40, 40);
	m_rtRight = RectMakeCenter(m_nPosX + 40, m_nPosY, 40, 40);

	RECT rt;
	m_rtViewPort = ViewPortMake(m_nPosX, m_nPosY, WINSIZEX - 200, WINSIZEY, 1080, 720);

	for (int y = 0; y < MaxY; y++)
	{
		for (int x = 0; x < MaxX; x++)
		{
			if (g_pKeyManager->isStayKeyDown(VK_LEFT) && IntersectRect(&rt, &m_rtLeft, &DungeonTile[x][y].rtTile) 
				&& DungeonTile[x][y].isMove == true)
			{
				if(m_nMoveDelay ==0)
				m_nPosX -= 40;
				m_nMoveDelay++;
				if (m_nMoveDelay >= DELAY)
					m_nMoveDelay = 0;
			}
			else if (g_pKeyManager->isStayKeyDown(VK_RIGHT) && IntersectRect(&rt, &m_rtRight, &DungeonTile[x][y].rtTile)
				&& DungeonTile[x][y].isMove == true)
			{
				if (m_nMoveDelay == 0)
					m_nPosX += 40;
				m_nMoveDelay++;
				if (m_nMoveDelay >= DELAY)
					m_nMoveDelay = 0;
			}
			else if (g_pKeyManager->isStayKeyDown(VK_UP) && IntersectRect(&rt, &m_rtTop, &DungeonTile[x][y].rtTile)
				&& DungeonTile[x][y].isMove == true)
			{
				if (m_nMoveDelay == 0)
					m_nPosY -= 40;
				m_nMoveDelay++;
				if (m_nMoveDelay >= DELAY)
					m_nMoveDelay = 0;
			}
			else if (g_pKeyManager->isStayKeyDown(VK_DOWN) && IntersectRect(&rt, &m_rtBottom, &DungeonTile[x][y].rtTile)
				&& DungeonTile[x][y].isMove == true)
			{
				if (m_nMoveDelay == 0)
					m_nPosY += 40;
				m_nMoveDelay++;
				if (m_nMoveDelay >= DELAY)
					m_nMoveDelay = 0;
			}
		}
	}
}

void cDungeon1::Render()
{
	g_pImageManager->Render("Dungeon1", m_pPlayBuffer->GetMemDC());
	RectangleMake(m_pPlayBuffer->GetMemDC(), m_rtPlayer);
	RectangleMake(m_pPlayBuffer->GetMemDC(), Error);
	m_pPlayBuffer->ViewPortRender(g_hDC, m_rtViewPort, WINSIZEX - 200, WINSIZEY);
}

void cDungeon1::Release()
{
}

void cDungeon1::LoadingImage()
{
	g_pImageManager->AddImage("Dungeon1", "images/DUNGEON1.bmp", 1080, 720);
}
