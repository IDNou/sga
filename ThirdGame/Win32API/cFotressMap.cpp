#include "stdafx.h"
#include "cFotressMap.h"
#include "cFotressPlayer.h"


cFotressMap::cFotressMap()
{
	m_pImgMap = g_pImageManager->FindImage("Map");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pImgBackground = g_pImageManager->FindImage("BackGround");
}

cFotressMap::~cFotressMap()
{
}

void cFotressMap::Setup()
{
	PosX = 0;
	PosY = 0;
}

void cFotressMap::Update()
{

	switch (m_pPlayer->GetPlayerTurn())
	{
	case FirstPlayer:
		if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 > 0
			&& m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 < m_pImgMapBuffer->GetWidth())
			PosX = m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX();
		else if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 < 0)
			PosX = WINSIZEX / 2;
		else if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 > m_pImgMapBuffer->GetWidth())
			PosX = m_pImgMapBuffer->GetWidth() - WINSIZEX / 2;

		if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 > 0
			&& m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 < m_pImgMapBuffer->GetHeight())
			PosY = m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY();
		else if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 < 0)
			PosY = WINSIZEY / 2;
		else if (m_pPlayer->GetVecPlayer()[FirstPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 > m_pImgMapBuffer->GetHeight())
			PosY = m_pImgMapBuffer->GetHeight() - WINSIZEY / 2;
		break;

	case SecondPlayer:
		if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 > 0
			&& m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 < m_pImgMapBuffer->GetWidth())
			PosX = m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX();
		else if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() - WINSIZEX / 2 < 0)
			PosX = WINSIZEX / 2;
		else if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosX() + WINSIZEX / 2 > m_pImgMapBuffer->GetWidth())
			PosX = m_pImgMapBuffer->GetWidth() - WINSIZEX / 2;

		if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 > 0
			&& m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 < m_pImgMapBuffer->GetHeight())
			PosY = m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY();
		else if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() - WINSIZEY / 2 < 0)
			PosY = WINSIZEY / 2;
		else if (m_pPlayer->GetVecPlayer()[SecondPlayer].t_pPlayerImage->GetPosY() + WINSIZEY / 2 > m_pImgMapBuffer->GetHeight())
			PosY = m_pImgMapBuffer->GetHeight() - WINSIZEY / 2;
		break;
	default:
		break;
	}

}

void cFotressMap::Render()
{
	m_pImgBackground->Render(g_hDC, 0, 0, PosX - WINSIZEX / 2, PosY - WINSIZEY / 2, m_pImgBackground->GetWidth(), m_pImgBackground->GetHeight());

	// 픽셀 충돌 처리용 이미지 버퍼에 그림을 그린다.
	m_pImgMap->Render(m_pImgMapBuffer->GetMemDC(), 0, 0);

	// 오브젝트가 있다면 m_pImgMapBuffer에 그린다.


	// 백버퍼에 그린다.
	//m_pImgMapBuffer->SetTransColor(false, RGB(0, 0, 0));
	/*m_pImgMapBuffer->Render(g_hDC, 0, 0, m_fPlayerX - WINSIZEX/2, m_fPlayerY - WINSIZEY/2, WINSIZEX, WINSIZEY);
	cout << m_fPlayerX << " " << m_fPlayerY << endl;*/
}