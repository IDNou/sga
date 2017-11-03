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

	m_fMaxHp = 100;
	m_fCurrHp = 100;
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
}

void cPlayer::Update()
{
	// �ȼ� �浹 ó�� ��ġ ����
	float probeX = m_pPlayerImage->GetPosX() + m_pMap->GetPosX();
	float probeY = m_pPlayerImage->GetPosY() + m_pMap->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2 + 1;

	// false ��� ������ ����
	//if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY))
	//{
	//	
	//	//// �������� �����ȼ� �˻�
	//	//int deepY = 0;
	//	//while (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, probeX, probeY - deepY - 1))
	//	//{
	//	//	++deepY;
	//	//}

	//	//// ���� ���� �� �� ���ӿ� ������ŭ ���� �ø��� ���� ����
	//	//m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - deepY);
	//	//m_fGravity = 0.0f;
	//}
	//else
	//{
	//	// �߷��� ����Ͽ� ����
	//	/*m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() + m_fGravity);
	//	m_fGravity += GRAVITY;*/
	//}

	// ȭ��󿡼��� ������ ���� ����
	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
	{
		
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
	{

	}

	// ü�¹� ������Ʈ
	m_pHpBar->SetPosX(m_pPlayerImage->GetPosX());
	m_pHpBar->SetPosY(m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2 - 10);
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
	m_pHpBar->Update();
}

void cPlayer::Render()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	BoudingLineMake(g_hDC, m_pPlayerImage->GetBoundingBox().left,
		m_pPlayerImage->GetBoundingBox().top,
		m_pPlayerImage->GetFrameWidth(),
		m_pPlayerImage->GetFrameHeight());

	DeleteObject(hSelectPen);
	DeleteObject(hPen);

	RectangleMakeCenter(m_pImgMapBuffer->GetMemDC(),
		m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2,
		m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2,
		30, 30);
	//cout << m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2 << " " << m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2  << endl;
	
	m_pPlayerImage->FrameRender(m_pImgMapBuffer->GetMemDC(),
		m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2,
		m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2,
		0,0);

	m_pHpBar->Render();
}