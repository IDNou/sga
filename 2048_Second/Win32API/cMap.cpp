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

	//// �ȼ� �浹 ó���� �̹��� ���ۿ� �׸��� �׸���.
	//m_pImgMap->Render(m_pImgMapBuffer->GetMemDC(), 0, 0);

	//// ������Ʈ�� �ִٸ� m_pImgMapBuffer�� �׸���.


	//// ����ۿ� �׸���.
	////m_pImgMapBuffer->SetTransColor(false, RGB(0, 0, 0));
	//m_pImgMapBuffer->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);
}