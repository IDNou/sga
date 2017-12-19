#include "stdafx.h"
#include "cMapTool.h"


void cMapTool::Setup()
{
	m_pImgTileMap = g_pImageManager->AddFrameImage("TileMap", "images/tilemap.bmp",
		640, 256, 20, 8, true, RGB(255, 255, 255));
	m_pImgDrawMap = g_pImageManager->AddEmptyImage("DrawMap", WINSIZEX, WINSIZEY);

	for (int y = 0; y < NUM_TILE_Y; ++y)
	{
		for (int x = 0; x < NUM_TILE_X; ++x)
		{
			m_stTileInfo[y][x].eTerrain = TR_WALKABLE;
			m_stTileInfo[y][x].eObject = OBJ_NONE;
			m_stTileInfo[y][x].ptTerrain = { 2, 0 };
		}
	}

	LoadMap();
}

void cMapTool::Update()
{
	// 타일맵 선택 영역
	if (g_ptMouse.x > 640 && g_ptMouse.y < 60 &&
		g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		SelectTerrain();
	}
	else if (g_ptMouse.x > 640 && g_ptMouse.y < 100 &&
		g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		SelectObject();
	}
	// 드로잉 영역
	else if (g_ptMouse.x < 640 && g_ptMouse.y < 480 &&
		g_pKeyManager->isStayKeyDown(VK_LBUTTON))
	{
		DrawMap();
	}
	else if (g_ptMouse.x < 640 && g_ptMouse.y < 480 &&
		g_pKeyManager->isStayKeyDown(VK_RBUTTON))
	{
		DeleteObject();
	}
	else if (g_pKeyManager->isStayKeyDown('L'))
	{
		LoadMap();
	}
}

void cMapTool::Render()
{
	RectangleMake(g_hDC, 0, 0, 640, 480);
	m_pImgDrawMap->Render(g_hDC, 0, 0);

	RectangleMake(g_hDC, 640, 0, 800, 600);
	//int colum = 0;
	//int row = 0;

	for (int y = 0; y < 20; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			//m_pImgTileMap->FrameRender(g_hDC, 640 + x * 20, y * 20, colum++, row, 20, 20);

			//if (colum == 20)
			//{
			//	colum = 0;
			//	row++;
			//}

			m_pImgTileMap->FrameRender(g_hDC, 640 + x * 20, y * 20,
				IMAGE_X(x, y), IMAGE_Y(x, y), 20, 20);
		}
	}

	RectangleMake(g_hDC, 0, 480, 640, 600);

	char szBuf[128];
	string str = "마우스 x 좌표 : ";
	itoa(g_ptMouse.x, szBuf, 10);
	str += szBuf;
	TextOut(g_hDC, 640, 420, str.c_str(), str.length());

	str = "마우스 y 좌표 : ";
	itoa(g_ptMouse.y, szBuf, 10);
	str += szBuf;
	TextOut(g_hDC, 640, 450, str.c_str(), str.length());
}

void cMapTool::Release()
{
}

void cMapTool::SelectTerrain()
{
	if (g_ptMouse.y < 20)
		m_stSelect.eTerrain = TR_UNWALKERABLE;
	else if (g_ptMouse.y < 40)
		m_stSelect.eTerrain = TR_WALKABLE;
	else if (g_ptMouse.y < 60)
		m_stSelect.eTerrain = TR_SWIMMABLE;

	m_stSelect.eObject = OBJ_NONE;

	m_stSelect.ptTerrain.x = (g_ptMouse.x - 640) / 20;
	m_stSelect.ptTerrain.y = g_ptMouse.y / 20;
}

void cMapTool::SelectObject()
{
	if (g_ptMouse.y < 120)
		m_stSelect.eObject = OBJ_NONEBREAKABLE;
	else if (g_ptMouse.y < 140)
		m_stSelect.eObject = OBJ_BREAKABLE;

	m_stSelect.ptObject.x = (g_ptMouse.x - 640) / 20;
	m_stSelect.ptObject.y = g_ptMouse.y / 20;
}

void cMapTool::DeleteObject()
{
	m_stTileInfo[g_ptMouse.y / 40][g_ptMouse.x / 40].eObject = OBJ_NONE;
	m_stTileInfo[g_ptMouse.y / 40][g_ptMouse.x / 40].eTerrain = TR_WALKABLE;

	POINT ptTile = m_stTileInfo[g_ptMouse.y / 40][g_ptMouse.x / 40].ptTerrain;

	m_pImgTileMap->FrameRender(m_pImgDrawMap->GetMemDC(),
		g_ptMouse.x / 40 * 40, g_ptMouse.y / 40 * 40,
		IMAGE_X(ptTile.x, ptTile.y), IMAGE_Y(ptTile.x, ptTile.y),
		TILE_SIZE_X, TILE_SIZE_Y);
}

void cMapTool::DrawMap()
{
	m_stTileInfo[g_ptMouse.y / 40][g_ptMouse.x / 40].eTerrain = m_stSelect.eTerrain;
	m_stTileInfo[g_ptMouse.y / 40][g_ptMouse.x / 40].eObject = m_stSelect.eObject;

	POINT ptDraw;

	if (m_stSelect.eObject == OBJ_NONE)
	{
		m_stTileInfo[g_ptMouse.y / 40][g_ptMouse.x / 40].ptTerrain = m_stSelect.ptTerrain;
		ptDraw.x = IMAGE_X(m_stSelect.ptTerrain.x, m_stSelect.ptTerrain.y);
		ptDraw.y = IMAGE_Y(m_stSelect.ptTerrain.x, m_stSelect.ptTerrain.y);
	}
	else
	{
		m_stTileInfo[g_ptMouse.y / 40][g_ptMouse.x / 40].ptObject = m_stSelect.ptObject;
		ptDraw.x = IMAGE_X(m_stSelect.ptObject.x, m_stSelect.ptObject.y);
		ptDraw.y = IMAGE_Y(m_stSelect.ptObject.x, m_stSelect.ptObject.y);
	}

	m_pImgTileMap->FrameRender(m_pImgDrawMap->GetMemDC(),
		g_ptMouse.x / 40 * 40, g_ptMouse.y / 40 * 40,
		ptDraw.x, ptDraw.y,	TILE_SIZE_X, TILE_SIZE_Y);
}

void cMapTool::LoadMap()
{
	POINT ptDraw;

	for (int y = 0; y < NUM_TILE_Y; ++y)
	{
		for (int x = 0; x < NUM_TILE_X; ++x)
		{
			if (m_stTileInfo[y][x].eObject == OBJ_NONE)
			{
				ptDraw.x = IMAGE_X(m_stTileInfo[y][x].ptTerrain.x, m_stTileInfo[y][x].ptTerrain.y);
				ptDraw.y = IMAGE_Y(m_stTileInfo[y][x].ptTerrain.x, m_stTileInfo[y][x].ptTerrain.y);

				m_pImgTileMap->FrameRender(m_pImgDrawMap->GetMemDC(), x * TILE_SIZE_X, y * TILE_SIZE_Y,
					ptDraw.x, ptDraw.y, TILE_SIZE_X, TILE_SIZE_Y);
			}
			else
			{
				ptDraw.x = IMAGE_X(m_stTileInfo[y][x].ptObject.x, m_stTileInfo[y][x].ptObject.y);
				ptDraw.y = IMAGE_Y(m_stTileInfo[y][x].ptObject.x, m_stTileInfo[y][x].ptObject.y);

				m_pImgTileMap->FrameRender(m_pImgDrawMap->GetMemDC(), x * TILE_SIZE_X, y * TILE_SIZE_Y,
					ptDraw.x, ptDraw.y, TILE_SIZE_X, TILE_SIZE_Y);
			}
		}
	}
}