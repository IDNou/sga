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
	m_fPlayerX = m_pPlayer->GetPosX();
	m_fPlayerY = m_pPlayer->GetPosY();
}

void cMap::Update()
{
	m_fPlayerX = m_pPlayer->GetPosX();
	m_fPlayerY = m_pPlayer->GetPosY();
}

void cMap::Render()
{
	m_pImgBackground->Render(g_hDC, 0, 0, 0, 0, m_pImgBackground->GetWidth(), m_pImgBackground->GetHeight());

	// �ȼ� �浹 ó���� �̹��� ���ۿ� �׸��� �׸���.
	m_pImgMap->Render(m_pImgMapBuffer->GetMemDC(), 0, 0);

	// ������Ʈ�� �ִٸ� m_pImgMapBuffer�� �׸���.


	// ����ۿ� �׸���.
	//m_pImgMapBuffer->SetTransColor(false, RGB(0, 0, 0));
	/*m_pImgMapBuffer->Render(g_hDC, 0, 0, m_fPlayerX - WINSIZEX/2, m_fPlayerY - WINSIZEY/2, WINSIZEX, WINSIZEY);
	cout << m_fPlayerX << " " << m_fPlayerY << endl;*/
}