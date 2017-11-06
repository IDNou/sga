#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
	/*m_pPlayerImage = g_pImageManager->FindImage("Player");
	m_pPlayerSecondImage = g_pImageManager->FindImage("Player2");*/
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	m_fMoveSpeed = 3.0f; //  *g_pTimeManager->GetDeltaTime();
	m_fGravity = 0.0f;
	
	Player.Number = FirstPlayer;
	Player.Dir = LEFT;
	Player.t_pPlayerImage = g_pImageManager->FindImage("Player");
	Player.m_pHpBar = new cProgressBar("ProgressBack", "ProgressFront", Player.t_pPlayerImage->GetWidth(), 10);
	Player.isDie = false;
	Player.m_fCurrHp = 100;
	Player.m_fMaxHp = 100;
	Player.m_pHpBar->SetGauge(Player.m_fCurrHp, Player.m_fMaxHp);
	Player.m_fGravity = 0;
	vecPlayer.push_back(Player);

	Player.Number = SecondPlayer;
	Player.Dir = RIGHT;
	Player.t_pPlayerImage = g_pImageManager->FindImage("Player2");
	Player.m_pHpBar = new cProgressBar("ProgressBack", "ProgressFront", Player.t_pPlayerImage->GetWidth(), 10);
	Player.isDie = false;
	Player.m_fCurrHp = 100;
	Player.m_fMaxHp = 100;
	Player.m_pHpBar->SetGauge(Player.m_fCurrHp, Player.m_fMaxHp);
	Player.m_fGravity = 0;
	vecPlayer.push_back(Player);

	checkTurn = FirstPlayer;

	//폭탄 설정
	m_pBomb = g_pImageManager->FindImage("Bomb");
	bombPosX = 0;
	bombPosY = 0;
	bombAngle = 45.0f;
	bombPower = 0;
	bombCount = 10;
	isBombActivity = false;
}

void cPlayer::Update()
{
	for (auto iter = vecPlayer.begin(); iter != vecPlayer.end(); ++iter)
	{
		float ProbeX = iter->t_pPlayerImage->GetPosX();
		float ProbeY = iter->t_pPlayerImage->GetPosY() + iter->t_pPlayerImage->GetHeight() / 2 + 5;
		float LProbeX = iter->t_pPlayerImage->GetPosX() - iter->t_pPlayerImage->GetWidth() / 2;
		float LProbeY = iter->t_pPlayerImage->GetPosY() + iter->t_pPlayerImage->GetHeight() / 2 + 5;
		float RProbeX = iter->t_pPlayerImage->GetPosX() + iter->t_pPlayerImage->GetWidth() / 2;
		float RProbeY = iter->t_pPlayerImage->GetPosY() + iter->t_pPlayerImage->GetHeight() / 2 + 5;
		
		if (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, ProbeX, ProbeY))
		{
			float deepY = 0;
			while (!g_pPixelManager->CheckPixel(m_pImgMapBuffer, ProbeX, ProbeY))
			{
				deepY += GRAVITY;
				ProbeY -= deepY;
			}

			iter->t_pPlayerImage->SetPosY(iter->t_pPlayerImage->GetPosY() - deepY);
			iter->m_fGravity = 0.0f;
		}
		else
		{
			iter->m_fGravity += GRAVITY;
			iter->t_pPlayerImage->SetPosY(iter->t_pPlayerImage->GetPosY() + iter->m_fGravity);
		}

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
		// 체력바 업데이트
		iter->m_pHpBar->SetPosX(iter->t_pPlayerImage->GetPosX());
		iter->m_pHpBar->SetPosY(iter->t_pPlayerImage->GetPosY() - iter->t_pPlayerImage->GetHeight() / 2);
		iter->m_pHpBar->SetGauge(iter->m_fMaxHp, iter->m_fCurrHp);
		iter->m_pHpBar->Update();
	}
}

void cPlayer::Render()
{
	for (auto iter = vecPlayer.begin(); iter != vecPlayer.end(); ++iter)
	{
	//	RectangleMakeCenter(m_pImgMapBuffer->GetMemDC(), iter->t_pPlayerImage->GetPosX(), iter->t_pPlayerImage->GetPosY() + 10, 45, 45);
		

		HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
		HPEN hSelectPen = (HPEN)SelectObject(m_pImgMapBuffer->GetMemDC(), hPen);

		MoveToEx(m_pImgMapBuffer->GetMemDC(), iter->t_pPlayerImage->GetPosX(), iter->t_pPlayerImage->GetPosY(), NULL);
		LineTo(m_pImgMapBuffer->GetMemDC(), iter->t_pPlayerImage->GetPosX()+bombPosX, iter->t_pPlayerImage->GetPosY()+bombPosY);

		DeleteObject(hSelectPen);
		DeleteObject(hPen);

		if(iter->Dir == LEFT)
			iter->t_pPlayerImage->FrameRender(m_pImgMapBuffer->GetMemDC(),
				iter->t_pPlayerImage->GetPosX() - iter->t_pPlayerImage->GetFrameWidth() / 2,
				iter->t_pPlayerImage->GetPosY() - iter->t_pPlayerImage->GetFrameHeight() / 2,
				0, 0);
		else if(iter->Dir == RIGHT)
			iter->t_pPlayerImage->FrameRender(m_pImgMapBuffer->GetMemDC(),
				iter->t_pPlayerImage->GetPosX() - iter->t_pPlayerImage->GetFrameWidth() / 2,
				iter->t_pPlayerImage->GetPosY() - iter->t_pPlayerImage->GetFrameHeight() / 2,
				1, 0);

		iter->m_pHpBar->Render(m_pImgMapBuffer->GetMemDC());

		switch (checkTurn)
		{
		case FirstPlayer:
			if (iter->Number == checkTurn)
				WhoRender(vecPlayer[FirstPlayer]);
			break;
		case SecondPlayer:
			if (iter->Number == checkTurn)
				WhoRender(vecPlayer[SecondPlayer]);
			break;
		default:
			break;
		}
	}
}

void cPlayer::WhoUpdate(tagPlayer &t_pPlayer)
{
	bombPosX = (-sinf(PI / 180 * bombAngle) * 50);
	bombPosY = (cosf(PI / 180 * bombAngle) * 50);

	// 화면상에서의 움직임 범위 제한
	if (g_pKeyManager->isStayKeyDown(VK_LEFT) 
		&& t_pPlayer.t_pPlayerImage->GetPosX() - t_pPlayer.t_pPlayerImage->GetWidth()/2 > 0)
	{
		t_pPlayer.Dir = LEFT;
		bombAngle = 135.0f;
		t_pPlayer.t_pPlayerImage->SetPosX(t_pPlayer.t_pPlayerImage->GetPosX() - m_fMoveSpeed);
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT)
		&& t_pPlayer.t_pPlayerImage->GetPosX() + t_pPlayer.t_pPlayerImage->GetWidth() / 2 < m_pImgMapBuffer->GetWidth())
	{
		t_pPlayer.Dir = RIGHT;
		bombAngle = 45.0f;
		t_pPlayer.t_pPlayerImage->SetPosX(t_pPlayer.t_pPlayerImage->GetPosX() + m_fMoveSpeed);
	}

	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		if (t_pPlayer.Dir == LEFT)
		{
			if (bombAngle < 90)
				++bombAngle;
		}
		else if (t_pPlayer.Dir == RIGHT)
		{
			if (bombAngle < 90)
				--bombAngle;
		}
	}
	if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		if (t_pPlayer.Dir == LEFT)
		{
			if (bombAngle > 180)
				--bombAngle;
		}
		else if (t_pPlayer.Dir == RIGHT)
		{
			if (bombAngle > 0)
				++bombAngle;
		}
	}

	if (g_pKeyManager->isStayKeyDown(VK_SPACE))
	{
		++bombPower;
	}

	if (g_pKeyManager->isOnceKeyUp(VK_SPACE))
	{
		isBombActivity = true;

		/*switch (checkTurn)
		{
		case FirstPlayer:
			checkTurn = SecondPlayer;
			break;
		case SecondPlayer:
			checkTurn = FirstPlayer;
			break;
		default:
			break;
		}*/
	}

	//땅에 떨어지면 죽는다
	if (t_pPlayer.t_pPlayerImage->GetPosY() + t_pPlayer.t_pPlayerImage->GetHeight() / 2 > m_pImgMapBuffer->GetHeight())
	{
		t_pPlayer.isDie = true;
	}

}

void cPlayer::WhoRender(tagPlayer &t_pPlayer)
{
	if (isBombActivity)
	{
		m_pBomb->FrameRender(m_pImgMapBuffer->GetMemDC(), t_pPlayer.t_pPlayerImage->GetPosX()+ bombPosX, t_pPlayer.t_pPlayerImage->GetPosY() + bombPosY, m_pBomb->GetFrameX(), 0);
		if (bombCount < 0)
		{
			bombCount = 10;
			m_pBomb->SetFrameX(m_pBomb->GetFrameX() + 1);
		}
		if(m_pBomb->GetFrameX() >m_pBomb->GetMaxFrameX())
			m_pBomb->SetFrameX(0);

		bombCount--;
	}
}