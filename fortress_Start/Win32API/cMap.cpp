#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"


cMap::cMap()
{
	m_pImgMap = g_pImageManager->FindImage("Map");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pImgBackground = g_pImageManager->FindImage("BackGround");
}

cMap::~cMap()
{
}

void cMap::Setup()
{
	m_fPosX = 0.0f;
	m_fPosY = 0.0f;
}

void cMap::Update()
{
	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
	{

	}
	if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{

	}
}

void cMap::Render()
{
	m_pImgBackground->Render(g_hDC, 0, 0, m_fPosX, m_fPosY, WINSIZEX, WINSIZEY);

	// �ȼ� �浹 ó���� �̹��� ���ۿ� �׸��� �׸���.
	m_pImgMap->Render(m_pImgMapBuffer->GetMemDC(), 0, 0);

	// ������Ʈ�� �ִٸ� m_pImgMapBuffer�� �׸���.


	// ����ۿ� �׸���.
	//m_pImgMapBuffer->SetTransColor(false, RGB(0, 0, 0));
	m_pImgMapBuffer->Render(g_hDC, 0, 0, m_fPosX, m_fPosY, WINSIZEX, WINSIZEY);
}