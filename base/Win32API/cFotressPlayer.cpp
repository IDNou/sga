#include "stdafx.h"
#include "cFotressPlayer.h"
#include "cProgressBar.h"
#include "cFotressMap.h"


cFotressPlayer::cFotressPlayer()
{
	/*m_pPlayerImage = g_pImageManager->FindImage("Player");
	m_pPlayerSecondImage = g_pImageManager->FindImage("Player2");*/
	m_pBackGround = g_pImageManager->FindImage("BackGround");
	m_pImgMap = g_pImageManager->FindImage("Map");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
}


cFotressPlayer::~cFotressPlayer()
{
}

void cFotressPlayer::Setup()
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

	//��ź ����
	m_pBomb = g_pImageManager->FindImage("Bomb");
	bombPosX = 0;
	bombPosY = 0;
	bombAngle = 45.0f;
	bombPower = 0;
	bombCount = 10;
	isBombActivity = false;
}

void cFotressPlayer::Update()
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
			if (iter->Number == checkTurn)
				WhoUpdate(vecPlayer[FirstPlayer]);
			break;
		case SecondPlayer:
			if (iter->Number == checkTurn)
				WhoUpdate(vecPlayer[SecondPlayer]);
			break;
		default:
			break;
		}
		// ü�¹� ������Ʈ
		iter->m_pHpBar->SetPosX(iter->t_pPlayerImage->GetPosX());
		iter->m_pHpBar->SetPosY(iter->t_pPlayerImage->GetPosY() - iter->t_pPlayerImage->GetHeight() / 2);
		iter->m_pHpBar->SetGauge(iter->m_fMaxHp, iter->m_fCurrHp);
		iter->m_pHpBar->Update();
	}
}

void cFotressPlayer::Render()
{
	for (auto iter = vecPlayer.begin(); iter != vecPlayer.end(); ++iter)
	{
		//	RectangleMakeCenter(m_pImgMapBuffer->GetMemDC(), iter->t_pPlayerImage->GetPosX(), iter->t_pPlayerImage->GetPosY() + 10, 45, 45);


		HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
		HPEN hSelectPen = (HPEN)SelectObject(m_pImgMapBuffer->GetMemDC(), hPen);

		MoveToEx(m_pImgMapBuffer->GetMemDC(), iter->t_pPlayerImage->GetPosX(), iter->t_pPlayerImage->GetPosY(), NULL);
		LineTo(m_pImgMapBuffer->GetMemDC(), iter->t_pPlayerImage->GetPosX() + bombPosX * 50, iter->t_pPlayerImage->GetPosY() + bombPosY * 50);

		DeleteObject(hSelectPen);
		DeleteObject(hPen);

		if (iter->Dir == LEFT)
			iter->t_pPlayerImage->FrameRender(m_pImgMapBuffer->GetMemDC(),
				iter->t_pPlayerImage->GetPosX() - iter->t_pPlayerImage->GetFrameWidth() / 2,
				iter->t_pPlayerImage->GetPosY() - iter->t_pPlayerImage->GetFrameHeight() / 2,
				0, 0);
		else if (iter->Dir == RIGHT)
			iter->t_pPlayerImage->FrameRender(m_pImgMapBuffer->GetMemDC(),
				iter->t_pPlayerImage->GetPosX() - iter->t_pPlayerImage->GetFrameWidth() / 2,
				iter->t_pPlayerImage->GetPosY() - iter->t_pPlayerImage->GetFrameHeight() / 2,
				1, 0);

		iter->m_pHpBar->Render();

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

void cFotressPlayer::WhoUpdate(tagPlayer &t_pPlayer)
{
	if (!isBombActivity)
	{
		bombPosX = cosf(PI / 180 * bombAngle);
		bombPosY = -sinf(PI / 180 * bombAngle);

		// ȭ��󿡼��� ������ ���� ����
		if (g_pKeyManager->isStayKeyDown(VK_LEFT)
			&& t_pPlayer.t_pPlayerImage->GetPosX() - t_pPlayer.t_pPlayerImage->GetWidth() / 2 > 0)
		{
			t_pPlayer.Dir = LEFT;
			t_pPlayer.t_pPlayerImage->SetPosX(t_pPlayer.t_pPlayerImage->GetPosX() - m_fMoveSpeed);
		}
		else if (g_pKeyManager->isStayKeyDown(VK_RIGHT)
			&& t_pPlayer.t_pPlayerImage->GetPosX() + t_pPlayer.t_pPlayerImage->GetWidth() / 2 < m_pImgMapBuffer->GetWidth())
		{
			t_pPlayer.Dir = RIGHT;
			t_pPlayer.t_pPlayerImage->SetPosX(t_pPlayer.t_pPlayerImage->GetPosX() + m_fMoveSpeed);
		}

		if (g_pKeyManager->isStayKeyDown(VK_UP))
		{
			if (t_pPlayer.Dir == LEFT)
			{
				if (bombAngle > 90)
					--bombAngle;
			}
			else if (t_pPlayer.Dir == RIGHT)
			{
				if (bombAngle < 90)
					++bombAngle;
			}
		}
		if (g_pKeyManager->isStayKeyDown(VK_DOWN))
		{
			if (t_pPlayer.Dir == LEFT)
			{
				if (bombAngle < 180)
					++bombAngle;
			}
			else if (t_pPlayer.Dir == RIGHT)
			{
				if (bombAngle > 0)
					--bombAngle;
			}
		}

		if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		{
			bombPower = 0;
		}
		if (g_pKeyManager->isStayKeyDown(VK_SPACE))
		{
			++bombPower;
		}
		if (g_pKeyManager->isOnceKeyUp(VK_SPACE))
		{
			isBombActivity = true;
			m_pBomb->SetPosX(t_pPlayer.t_pPlayerImage->GetPosX() + bombPosX * 50);
			m_pBomb->SetPosY(t_pPlayer.t_pPlayerImage->GetPosY() + bombPosY * 50);

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

		//���� �������� �״´�
		if (t_pPlayer.t_pPlayerImage->GetPosY() + t_pPlayer.t_pPlayerImage->GetHeight() / 2 > m_pImgMapBuffer->GetHeight())
		{
			t_pPlayer.isDie = true;
		}
	}
}

void cFotressPlayer::WhoRender(tagPlayer &t_pPlayer)
{
	if (isBombActivity)
	{
		m_pBomb->FrameRender(m_pImgMapBuffer->GetMemDC(), m_pBomb->GetPosX(),
			m_pBomb->GetPosY(), m_pBomb->GetFrameX(), 0);
		if (bombCount < 0)
		{
			bombCount = 10;
			m_pBomb->SetFrameX(m_pBomb->GetFrameX() + 1);
		}
		if (m_pBomb->GetFrameX() >m_pBomb->GetMaxFrameX())
			m_pBomb->SetFrameX(0);

		m_fGravity += GRAVITY;
		m_pBomb->SetPosX(m_pBomb->GetPosX() + bombPosX*bombPower / 4);
		m_pBomb->SetPosY(m_pBomb->GetPosY() + bombPosY*bombPower / 4 + m_fGravity);

		if (m_fGravity > bombPosY*bombPower / 4)
		{
			if (g_pPixelManager->CheckPixel(m_pImgMapBuffer, m_pBomb->GetPosX(), m_pBomb->GetPosY()) == false)
			{// ����ٰ� ������ ���鲨��
				g_pPixelManager->RemoveBrush(m_pImgMap, m_pBomb->GetPosX(), m_pBomb->GetPosY(), 50);
				//g_pPixelManager->RemoveBrush(m_pBackGround, m_pBomb->GetPosX(), m_pBomb->GetPosY(), 50);
				cout << " �߰�" << endl;
			}
		}

		bombCount--;
	}
}