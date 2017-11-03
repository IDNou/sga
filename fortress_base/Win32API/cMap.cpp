#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cObjects.h"


cMap::cMap()
{
	m_pImgBackgoround = g_pImageManager->FindImage("Map");
	m_pImgGround = g_pImageManager->FindImage("Map_Magenta");
}

cMap::~cMap()
{
}

void cMap::Setup()
{
	PosX = 0;
	PosY = 0;
	MapPosX = 0;
	MapPosY = 0;
}

void cMap::Update()
{

	if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{
		if(PosX+WINSIZEX < m_pImgBackgoround->GetWidth())
			PosX += 5;
	}
	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
	{
		if(PosX >0)
			PosX -= 5;
	}
	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		if(PosY >0)
			PosY -= 5;
	}
	if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		if(PosY + WINSIZEY < m_pImgBackgoround->GetHeight())
			PosY += 5;
	}
}

void cMap::Render()
{
	
	m_pImgBackgoround->Render(g_hDC, 0, 0, MapPosX , MapPosY , WINSIZEX, WINSIZEY, WINSIZEX, WINSIZEY);
	RectangleMake(g_hDC, PosX, PosY, 50, 50);
	

//	m_pImgGround->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgGround->GetFrameHeight());
}