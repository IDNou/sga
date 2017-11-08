#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cObject.h"


cMap::cMap()
{
	m_pImgMap = g_pImageManager->FindImage("Map");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
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
	//RectangleMakeCenter(g_hDC, 100, 200, 50, 50);

	//// 픽셀 충돌 처리용 이미지 버퍼에 그림을 그린다.
	//m_pImgMap->Render(m_pImgMapBuffer->GetMemDC(), 0, 0);

	//// 오브젝트가 있다면 m_pImgMapBuffer에 그린다.


	//// 백버퍼에 그린다.
	////m_pImgMapBuffer->SetTransColor(false, RGB(0, 0, 0));
	//m_pImgMapBuffer->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);
}