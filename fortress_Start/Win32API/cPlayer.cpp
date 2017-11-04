#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
	m_pPlayerImage = g_pImageManager->FindImage("Player");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");

	m_pHpBar = new cProgressBar("ProgressBack", "ProgressFront",
		m_pPlayerImage->GetFrameWidth(), 10);
}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	m_fMoveSpeed = 3.0f; //  *g_pTimeManager->GetDeltaTime();
	m_isMapMove = false;
	isDie = false;

	m_fMaxHp = 100;
	m_fCurrHp = 100;
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
}

void cPlayer::Update()
{
	// 픽셀 충돌 처리 위치 설정
	float probeX = m_pPlayerImage->GetPosX() ;
	float probeY = m_pPlayerImage->GetPosY() + (m_pPlayerImage->GetFrameHeight() / 2) + 5;

	// false 경우 땅위에 착지
	if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY))
	{
		// 땅속으로 묻힌픽셀 검사
		float deepY = 0;
		while (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY))
		{
			deepY += GRAVITY;
			probeY -= deepY;
		}

		// 땅에 착지 한 뒤 땅속에 박힌만큼 위로 올리고 낙하 종료
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - deepY);
		m_fGravity = 0.0f;
	}
	else
	{
		// 중력을 사용하여 낙하
		m_fGravity += GRAVITY;
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() + m_fGravity);
	}

	// 화면상에서의 움직임 범위 제한
	if (g_pKeyManager->isStayKeyDown(VK_LEFT) 
		&& m_pPlayerImage->GetPosX() - m_pPlayerImage->GetWidth()/2 > 0)
	{
		m_pPlayerImage->SetPosX(m_pPlayerImage->GetPosX() - 3);
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT)
		&& m_pPlayerImage->GetPosX() + m_pPlayerImage->GetWidth() / 2 < m_pImgMapBuffer->GetWidth())
	{
		m_pPlayerImage->SetPosX(m_pPlayerImage->GetPosX() + 3);
	}

	if (m_pPlayerImage->GetPosY() + m_pPlayerImage->GetHeight() / 2 > m_pImgMapBuffer->GetHeight())
	{
		isDie = true;
	}
	
	//// 체력바 업데이트
	//m_pHpBar->SetPosX(m_pPlayerImage->GetPosX());
	//m_pHpBar->SetPosY(m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2 - 10);
	//m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
	//m_pHpBar->Update();
}

void cPlayer::Render()
{
	if (!isDie)
	{
		HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
		HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

		BoudingLineMake(m_pImgMapBuffer->GetMemDC(), m_pPlayerImage->GetBoundingBox().left,
			m_pPlayerImage->GetBoundingBox().top,
			m_pPlayerImage->GetFrameWidth(),
			m_pPlayerImage->GetFrameHeight());

		DeleteObject(hSelectPen);
		DeleteObject(hPen);

		RectangleMakeCenter(m_pImgMapBuffer->GetMemDC(),
			m_pPlayerImage->GetPosX(),
			m_pPlayerImage->GetPosY(),
			60, 60);

		m_pPlayerImage->FrameRender(m_pImgMapBuffer->GetMemDC(),
			m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2,
			m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2,
			0, 0);

		/*m_pHpBar->Render();*/
	}
}