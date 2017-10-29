#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"
#include "cObjects.h"


cPlayer::cPlayer()
{
	m_pPlayerImage = g_pImageManager->FindImage("MarioRight");

	m_pMapImg = g_pImageManager->FindImage("Map_Magenta");
}


cPlayer::~cPlayer()
{
	vector<string> saveData;
	char temp[128];

	saveData.push_back(itoa(m_fPosX, temp, 10));
	saveData.push_back(itoa(m_fPosY, temp, 10));

	g_pFileDataManager->txtSave("PlayerData.txt", saveData);
}

void cPlayer::Setup()
{
	m_pPlayerImage->SetPosX(200);
	m_pPlayerImage->SetPosY(400);
	m_nDamageDelay = 0;
	m_nMapYPos = MAP1_Y;
	m_fJumpPower = 10.0f;
	frameCount = 10;
	isDie = false;

	SetLanding();

	/*vector<string> vecLoad = g_pFileDataManager->txtLoad("PlayerData.txt");

	if (!vecLoad.empty())
	{
		m_pPlayerImage->SetPosX(atoi(vecLoad[0].c_str()));
		m_pPlayerImage->SetPosY(atoi(vecLoad[1].c_str()));
		m_fCurrHp = atoi(vecLoad[2].c_str());
	}*/
}

void cPlayer::Update()
{
	BprobeX = m_pPlayerImage->GetPosX();
	BprobeY = m_pPlayerImage->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2;

	LprobeX = m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2;
	LprobeY = m_pPlayerImage->GetPosY();

	RprobeX = m_pPlayerImage->GetPosX() + m_pPlayerImage->GetFrameWidth() / 2;
	RprobeY = m_pPlayerImage->GetPosY();

	TprobeX = m_pPlayerImage->GetPosX();
	TprobeY = m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2;

	if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX + m_pMap->GetMoveX(), BprobeY))
	{
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() + 5);
	}
	else if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX + m_pMap->GetMoveX(), BprobeY - 5) == false
		&& !m_isJumpping)
	{
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - 5);
	}

	if (g_pKeyManager->isStayKeyDown(VK_LEFT) 
		&& g_pPixelManager->CheckPixel(m_pMapImg, LprobeX + m_pMap->GetMoveX(), LprobeY))
	{
		if (m_pPlayerImage->GetPosX() > 200)
			m_pPlayerImage->SetPosX(m_fPosX - 5.0f);
		else
		{
			if (m_pMap->GetMoveX() > 0)
			{
				m_pMap->SetMoveX(m_pMap->GetMoveX() - 5);
			}
			else
				m_pPlayerImage->SetPosX(m_fPosX - 5.0f);
		}
			
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT) 
		&& g_pPixelManager->CheckPixel(m_pMapImg, RprobeX + m_pMap->GetMoveX(), RprobeY))
	{
		if (frameCount < 0)
		{
			frameCount = 10;
			m_pPlayerImage->SetFrameX(m_pPlayerImage->GetFrameX() + 1);
		}

		if (m_pPlayerImage->GetFrameX() > m_pPlayerImage->GetMaxFrameX())
			m_pPlayerImage->SetFrameX(1);

		if (m_pPlayerImage->GetPosX() < WINSIZEX/2 + 100)
			m_pPlayerImage->SetPosX(m_fPosX + 5.0f);
		else
		{	
			if (m_pMap->GetMoveX() < m_pMapImg->GetFrameWidth() - 810)
			{
				m_pMap->SetMoveX(m_pMap->GetMoveX() + 5);
				
			}
			else
				m_pPlayerImage->SetPosX(m_fPosX + 5.0f);
		}
		--frameCount;
	}

#ifdef _DEBUG
	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		m_pPlayerImage->SetPosY(m_fPosY - 3.0f);
	}
	else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		m_pPlayerImage->SetPosY(m_fPosY + 3.0f);
	}
#endif // _DEBUGH

	if (!m_isJumpping && g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		m_isJumpping = true;
	}

	RECT rt;
	if (m_isJumpping)
	{
		m_pPlayerImage->SetPosY(m_fPosY - m_fJumpPower + m_fGravity);
		m_fGravity += GRAVITY;

		if (g_pPixelManager->CheckPixel(m_pMapImg, TprobeX + m_pMap->GetMoveX(), TprobeY) == false)
		{
			m_fJumpPower = m_fGravity - 5.0f;

			for (auto iter = m_pMap->GetVecWall().begin(); iter != m_pMap->GetVecWall().end(); ++iter)
			{
				if (IntersectRect(&rt, &RectMakeCenter(TprobeX, TprobeY, 2, 2),&RectMake(iter->PosX - (m_pMap->GetMoveX()+5), iter->PosY, 40, 40)))
				{
					iter->isBreak = true;
				}
			}
		}

		// 점프 후 내려오는 중에 착지 설정
		if (m_fGravity > m_fJumpPower)
		{
			BprobeY = m_pPlayerImage->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2 + m_fGravity;

			if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX + m_pMap->GetMoveX(), BprobeY - 5) == false)
				
				SetLanding();
		}
	}

	
	if (BprobeY >= 600) {
		m_pPlayerImage->SetPosY(m_fPosY + 3.0f);
		if (TprobeY >= 610)
		{
			isDie = true;
		}	
	}
	if (RprobeX >= 800)
		isDie = true;

	m_fPosX = m_pPlayerImage->GetPosX();
	m_fPosY = m_pPlayerImage->GetPosY();

}

void cPlayer::MiniRender()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);
#ifdef _DEBUG


	EllipseMakeCenter(g_hDC, m_pPlayerImage->GetPosX(), m_pPlayerImage->GetPosY(), 10, 10);

#endif // _DEBUG

	DeleteObject(hSelectPen);
	DeleteObject(hPen);
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

	m_pPlayerImage->FrameRender(g_hDC,
		m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2,
		m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2, m_pPlayerImage->GetFrameX(), m_pPlayerImage->GetFrameY());
}

void cPlayer::SetLanding()
{
	m_fGravity = 0.0f;
	m_fJumpPower = 10.0f;
	m_isJumpping = false;
}