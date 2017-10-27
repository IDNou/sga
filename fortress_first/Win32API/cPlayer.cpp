#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
	//m_pPlayerImage = new cImage;
	//m_pPlayerImage->Setup("images/ch.bmp", 960, 960, 12, 12,
	//	200, MAP1_Y, true, RGB(255, 0, 255));

	m_pPlayerImage = g_pImageManager->FindImage("Player");

	m_pHpBar = new cProgressBar("HpBarBack", "HpBarFront",
		m_pPlayerImage->GetFrameWidth(), 10);

	m_pMapImg = g_pImageManager->FindImage("Map_Magenta");
}


cPlayer::~cPlayer()
{
	vector<string> saveData;
	char temp[128];

	saveData.push_back(itoa(m_fPosX, temp, 10));
	saveData.push_back(itoa(m_fPosY, temp, 10));
	saveData.push_back(itoa(m_fCurrHp, temp, 10));

	g_pFileDataManager->txtSave("PlayerData.txt", saveData);
}

void cPlayer::Setup()
{
	m_nDamageDelay = 0;
	m_nMapYPos = MAP1_Y;
	m_fJumpPower = 10.0f;

	m_fMaxHp = 100;
	m_fCurrHp = 100;
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);

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
	float BprobeX = m_pPlayerImage->GetPosX();
	float BprobeY = m_pPlayerImage->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2;
	float LprobeX = m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2;
	float LprobeY = m_pPlayerImage->GetPosY() + 10;
	float RprobeX = m_pPlayerImage->GetPosX() + m_pPlayerImage->GetFrameWidth() / 2;;
	float RprobeY = m_pPlayerImage->GetPosY();

	if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX + m_pMap->GetMoveX(), BprobeY))
	{
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() + 5);
	}
	else if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX + m_pMap->GetMoveX(), BprobeY - 5) == false
		//&& g_pPixelManager->CheckPixel(m_pMapImg, LprobeX, LprobeY)
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
				cout << m_pMap->GetMoveX() << endl;
			}
			else
				m_pPlayerImage->SetPosX(m_fPosX - 5.0f);
		}
			
	}
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT) 
		&& g_pPixelManager->CheckPixel(m_pMapImg, RprobeX + m_pMap->GetMoveX(), RprobeY))
	{
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
	}

	if (g_pKeyManager->isStayKeyDown(VK_UP))
	{
		m_pPlayerImage->SetPosY(m_fPosY - 3.0f);
	}
	else if (g_pKeyManager->isStayKeyDown(VK_DOWN))
	{
		m_pPlayerImage->SetPosY(m_fPosY + 3.0f);
	}

	if (!m_isJumpping && g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		m_isJumpping = true;
	}

	if (m_isJumpping)
	{
		m_pPlayerImage->SetPosY(m_fPosY - m_fJumpPower + m_fGravity);
		m_fGravity += GRAVITY;

		// 점프 후 내려오는 중에 착지 설정
		if (m_fGravity > m_fJumpPower)
		{
			BprobeY = m_pPlayerImage->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2 + m_fGravity;

			if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX + m_pMap->GetMoveX(), BprobeY - 5) == false
				&& g_pPixelManager->CheckPixel(m_pMapImg, LprobeX + m_pMap->GetMoveX(), LprobeY - 5)
				&& g_pPixelManager->CheckPixel(m_pMapImg, RprobeX + m_pMap->GetMoveX(), RprobeY - 5))
				SetLanding();
		}
	}

	if (m_nDamageDelay > 0)
		--m_nDamageDelay;

	m_fPosX = m_pPlayerImage->GetPosX();
	m_fPosY = m_pPlayerImage->GetPosY();

	m_pHpBar->SetPosX(m_fPosX);
	m_pHpBar->SetPosY(m_fPosY - m_pPlayerImage->GetFrameHeight() / 2 - 10);
	m_pHpBar->SetGauge(m_fMaxHp, m_fCurrHp);
	m_pHpBar->Update();
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

	//RectangleMake(g_hDC, m_pPlayerImage->GetBoundingBox(20, 5));
	BoudingLineMake(g_hDC, m_pPlayerImage->GetBoundingBox().left,
		m_pPlayerImage->GetBoundingBox().top,
		m_pPlayerImage->GetFrameWidth(),
		m_pPlayerImage->GetFrameHeight());

	DeleteObject(hSelectPen);
	DeleteObject(hPen);

	// 무적 모드 중에는 반짝이게 표현
	if (m_nDamageDelay % 2 == 0)
	{
		m_pPlayerImage->FrameRender(g_hDC,
			m_pPlayerImage->GetPosX() - m_pPlayerImage->GetFrameWidth() / 2,
			m_pPlayerImage->GetPosY() - m_pPlayerImage->GetFrameHeight() / 2,
			1, 0, 8, 0, 3);
	}

	//m_pMapImg->Render(g_hDC, 0, 0,0,0, WINSIZEX, WINSIZEY,WINSIZEX,m_pMapImg->GetFrameHeight());

	m_pHpBar->Render();
}

void cPlayer::SetLanding()
{
	m_fGravity = 0.0f;
	m_isJumpping = false;
}