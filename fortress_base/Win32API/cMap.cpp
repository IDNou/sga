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
	
}

void cMap::Update()
{
}

void cMap::Render()
{

	m_pImgBackgoround->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgBackgoround->GetFrameHeight());
//	m_pImgGround->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgGround->GetFrameHeight());
}