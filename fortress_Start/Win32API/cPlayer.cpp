#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
	/*m_pPlayerImage = g_pImageManager->FindImage("Player");
	m_pPlayerSecondImage = g_pImageManager->FindImage("Player2");*/
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
	m_pBomb = g_pImageManager->FindImage("Bomb");

	/*m_pHpBar = new cProgressBar("ProgressBack", "ProgressFront",
		m_pPlayerImage->GetFrameWidth(), 10);*/
}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	m_fMoveSpeed = 3.0f; //  *g_pTimeManager->GetDeltaTime();
	m_fGravity = 0.0f;
	
	Player.Number = FirstPlayer;
	Player.t_pPlayerImage = g_pImageManager->FindImage("Player");
	Player.isDie = false;
	Player.m_fCurrHp = 100;
	Player.m_fMaxHp = 100;
	Player.m_fGravity = 0;
	vecPlayer.push_back(Player);

	Player.Number = SecondPlayer;
	Player.t_pPlayerImage = g_pImageManager->FindImage("Player2");
	Player.isDie = false;
	Player.m_fCurrHp = 100;
	Player.m_fMaxHp = 100;
	Player.m_fGravity = 0;
	vecPlayer.push_back(Player);

	checkTurn = FirstPlayer;

	//폭탄 설정
	bombPosX = 0;
	bombPosY = 0;
	bombAngle = 0;
	bombPower = 0;
	isBombActivity = false;


	/*m_fMaxHp = 100;
	m_fCurrHp = 100;
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);*/
}

void cPlayer::Update()
{
	for (auto iter = vecPlayer.begin(); iter != vecPlayer.end(); ++iter)
	{
		/*float ProbeX = iter->t_pPlayerImage->GetPosX();
		float ProbeY = iter->t_pPlayerImage->GetPosY(); + iter->t_pPlayerImage->GetHeight() / 2 + 5;
		cout << ProbeX << endl;

		if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, ProbeX, ProbeY))
		{
			float deepY = 0;
			while (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, ProbeX, ProbeY))
			{
				deepY += GRAVITY;
				ProbeY -= deepY;
			}
			if(iter->t_pPlayerImage->GetPosY() - deepY > 50)
				iter->t_pPlayerImage->SetPosY(iter->t_pPlayerImage->GetPosY() - deepY);
			iter->m_fGravity = 0.0f;
		}
		else
		{
			iter->m_fGravity += GRAVITY;
			iter->t_pPlayerImage->SetPosY(iter->t_pPlayerImage->GetPosY() + iter->m_fGravity);
		}*/

		switch (checkTurn)
		{
		case FirstPlayer:
			if(iter->Number == checkTurn)
				WhoUpdate(vecPlayer[FirstPlayer]);
			break;
		case SecondPlayer:
			if (iter->Number == checkTurn)
				WhoUpdate(vecPlayer[SecondPlayer]);
			break;
		default:
			break;
		}
	}
}

void cPlayer::Render()
{
	for (auto iter = vecPlayer.begin(); iter != vecPlayer.end(); ++iter)
	{
			iter->t_pPlayerImage->FrameRender(m_pImgMapBuffer->GetMemDC(),
				iter->t_pPlayerImage->GetPosX() - iter->t_pPlayerImage->GetFrameWidth() / 2,
				iter->t_pPlayerImage->GetPosY() - iter->t_pPlayerImage->GetFrameHeight() / 2,
			0, 0);
	}
}

void cPlayer::WhoUpdate(tagPlayer t_pPlayer)
{

	float ProbeX = t_pPlayer.t_pPlayerImage->GetPosX();
	float ProbeY = t_pPlayer.t_pPlayerImage->GetPosY() + t_pPlayer.t_pPlayerImage->GetHeight() / 2 + 10;
	float LProbeX = t_pPlayer.t_pPlayerImage->GetPosX() - t_pPlayer.t_pPlayerImage->GetWidth() / 2;
	float LProbeY = t_pPlayer.t_pPlayerImage->GetPosY() + t_pPlayer.t_pPlayerImage->GetHeight() / 2;
	float RProbeX = t_pPlayer.t_pPlayerImage->GetPosX() + t_pPlayer.t_pPlayerImage->GetWidth() / 2;
	float RProbeY = t_pPlayer.t_pPlayerImage->GetPosY() + t_pPlayer.t_pPlayerImage->GetHeight() / 2;

	if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, ProbeX, ProbeY))
	{
		float deepY = 0;
		while (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, ProbeX, ProbeY))
		{
			deepY += GRAVITY;
			ProbeY -= deepY;
		}

		t_pPlayer.t_pPlayerImage->SetPosY(t_pPlayer.t_pPlayerImage->GetPosY() - deepY);
		m_fGravity = 0.0f;
	}
	else
	{
		m_fGravity += GRAVITY;
		t_pPlayer.t_pPlayerImage->SetPosY(t_pPlayer.t_pPlayerImage->GetPosY() + m_fGravity);
	}


	// 화면상에서의 움직임 범위 제한
	if (g_pKeyManager->isStayKeyDown(VK_LEFT) 
		&& t_pPlayer.t_pPlayerImage->GetPosX() - t_pPlayer.t_pPlayerImage->GetWidth()/2 > 0)
	{
		t_pPlayer.t_pPlayerImage->SetPosX(t_pPlayer.t_pPlayerImage->GetPosX() - m_fMoveSpeed);
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT)
		&& t_pPlayer.t_pPlayerImage->GetPosX() + t_pPlayer.t_pPlayerImage->GetWidth() / 2 < m_pImgMapBuffer->GetWidth())
	{
		t_pPlayer.t_pPlayerImage->SetPosX(t_pPlayer.t_pPlayerImage->GetPosX() + m_fMoveSpeed);
	}

	if (g_pKeyManager->isStayKeyDown(VK_SPACE))
	{
		++bombPower;
	}

	if (g_pKeyManager->isOnceKeyUp(VK_SPACE))
	{


		switch (checkTurn)
		{
		case FirstPlayer:
			checkTurn = SecondPlayer;
			break;
		case SecondPlayer:
			checkTurn = FirstPlayer;
			break;
		default:
			break;
		}
	}

	//땅에 떨어지면 죽는다
	if (t_pPlayer.t_pPlayerImage->GetPosY() + t_pPlayer.t_pPlayerImage->GetHeight() / 2 > m_pImgMapBuffer->GetHeight())
	{
		t_pPlayer.isDie = true;
	}
	
	// 체력바 업데이트
	/*m_pHpBar->SetPosX(m_pPlayerImage->GetPosX());
	m_pHpBar->SetPosY(m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2 - 10);
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
	m_pHpBar->Update();*/
}