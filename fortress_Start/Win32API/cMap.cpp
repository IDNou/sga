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
	PosX = 0;
	PosY = 0;
}

void cMap::Update()
{

	switch (m_pPlayer->GetPlayerTurn())
	{
	case FirstPlayer:
		if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 > 0 
			&& m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 < m_pImgMapBuffer->GetWidth())
			PosX = m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX();
		if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 > 0 
			&& m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 < m_pImgMapBuffer->GetHeight())
			PosY = m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY();
		break;
	case SecondPlayer:
		if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 > 0 
			&& m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 < m_pImgMapBuffer->GetWidth())
			PosX = m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX();
		if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 > 0
			&& m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 < m_pImgMapBuffer->GetHeight())
			PosY = m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY();
		break;
	default:
		break;
	}

}

void cMap::Render()
{
	m_pImgBackground->Render(g_hDC, 0, 0, PosX - WINSIZEX / 2, PosY - WINSIZEY / 2, m_pImgBackground->GetWidth(), m_pImgBackground->GetHeight());

	// �ȼ� �浹 ó���� �̹��� ���ۿ� �׸��� �׸���.
	m_pImgMap->Render(m_pImgMapBuffer->GetMemDC(), 0, 0);

	// ������Ʈ�� �ִٸ� m_pImgMapBuffer�� �׸���.


	// ����ۿ� �׸���.
	//m_pImgMapBuffer->SetTransColor(false, RGB(0, 0, 0));
	/*m_pImgMapBuffer->Render(g_hDC, 0, 0, m_fPlayerX - WINSIZEX/2, m_fPlayerY - WINSIZEY/2, WINSIZEX, WINSIZEY);
	cout << m_fPlayerX << " " << m_fPlayerY << endl;*/
}