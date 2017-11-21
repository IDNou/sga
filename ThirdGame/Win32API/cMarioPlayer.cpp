#include "stdafx.h"
#include "cMarioPlayer.h"
#include "cProgressBar.h"
#include "cMarioMap.h"
#include "cMarioObject.h"


cMarioPlayer::cMarioPlayer()
{
	m_pPlayerImage = g_pImageManager->FindImage("MarioRight");
	m_pMapImg = g_pImageManager->FindImage("Map_Magenta");
}


cMarioPlayer::~cMarioPlayer()
{
	vector<string> saveData;
	char temp[128];

	saveData.push_back(itoa(m_fPosX, temp, 10));
	saveData.push_back(itoa(m_fPosY, temp, 10));

	
	g_pFileData->txtSave("PlayerData.txt", saveData);
}

void cMarioPlayer::Setup()
{
	m_pPlayerImage->SetPosX(200);
	m_pPlayerImage->SetPosY(400);
	m_nDamageDelay = 0;
	m_nMapYPos = MAP1_Y;
	m_fJumpPower = 10.0f;
	m_fEnermyJump = 6.0f;
	frameCount = 10;
	smallJump = false;
	isDie = false;
	isGiant = false;

	SetLanding();

	/*vector<string> vecLoad = g_pFileDataManager->txtLoad("PlayerData.txt");

	if (!vecLoad.empty())
	{
	m_pPlayerImage->SetPosX(atoi(vecLoad[0].c_str()));
	m_pPlayerImage->SetPosY(atoi(vecLoad[1].c_str()));
	m_fCurrHp = atoi(vecLoad[2].c_str());
	}*/
}

void cMarioPlayer::Update()
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
				m_pObject->SetMoveGroundX(m_pMap->GetMoveX());
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

		if (m_pPlayerImage->GetPosX() < WINSIZEX / 2 + 100)
			m_pPlayerImage->SetPosX(m_fPosX + 5.0f);
		else
		{
			if (m_pMap->GetMoveX() < m_pMapImg->GetFrameWidth() - 810)
			{
				m_pMap->SetMoveX(m_pMap->GetMoveX() + 5);
				m_pObject->SetMoveGroundX(m_pMap->GetMoveX());
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
#endif // 

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
				if (IntersectRect(&rt, &RectMakeCenter(TprobeX, TprobeY, 2, 2), &RectMake(iter->PosX - (m_pMap->GetMoveX() + 5), iter->PosY, 40, 40))
					&& iter->type == eWall)
				{
					iter->isBreak = true;
				}
				else if (IntersectRect(&rt, &RectMakeCenter(TprobeX, TprobeY, 2, 2), &RectMake(iter->PosX - (m_pMap->GetMoveX() + 5), iter->PosY, 40, 40))
					&& iter->type == eMushRoomBox)
				{
					for (auto iter2 = m_pObject->GetMushRoomItem().begin(); iter2 != m_pObject->GetMushRoomItem().end(); ++iter2)
					{
						if (iter->MushRoomItemNum == iter2->objMushRoomItemNum)
							iter2->isActiveMushRoomItem = true;
					}
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

	RECT MushRoomRt;
	for (auto iter = m_pObject->GetMushRoomItem().begin(); iter != m_pObject->GetMushRoomItem().end(); ++iter)
	{
		if (IntersectRect(&MushRoomRt, &RectMake(m_pPlayerImage->GetBoundingBox().left, m_pPlayerImage->GetBoundingBox().top, m_pPlayerImage->GetFrameWidth(), m_pPlayerImage->GetFrameHeight()),
			&RectMake(iter->PosX - m_pMap->GetMoveX(), iter->PosY, 37, 40))
			&& iter->isActiveMushRoomItem)
		{
			isGiant = true;
			int posx = m_pPlayerImage->GetPosX();
			int posy = m_pPlayerImage->GetPosY();
			m_pPlayerImage = g_pImageManager->FindImage("MarioRight2");
			m_pPlayerImage->SetPosX(posx);
			m_pPlayerImage->SetPosY(posy);
			iter->isDie = true;
		}
	}

	//바 타고가는거
	RECT tc;
	if (IntersectRect(&tc, &RectMakeCenter(BprobeX, BprobeY, 40, 2),
		&RectMake(m_pObject->GetMoveBar()->GetPosX() + m_pObject->GetMoveBar()->GetFrameWidth() / 2 - m_pMap->GetMoveX(), m_pObject->GetMoveBar()->GetPosY(),
			m_pObject->GetMoveBar()->GetWidth(), m_pObject->GetMoveBar()->GetHeight())))
	{
		SetLanding();
		m_pPlayerImage->SetPosY(m_pPlayerImage->GetPosY() - 5);

		if (m_pPlayerImage->GetPosX() < WINSIZEX / 2 + 100)
			m_pPlayerImage->SetPosX(m_fPosX + 1.0f);
		else
		{
			if (m_pMap->GetMoveX() < m_pMapImg->GetFrameWidth() - 810)
			{
				m_pMap->SetMoveX(m_pMap->GetMoveX() + 1);
				m_pObject->SetMoveGroundX(m_pMap->GetMoveX());
			}
			else
				m_pPlayerImage->SetPosX(m_fPosX + 1.0f);
		}
	}


	// 버섯몬스터
	RECT ct;
	for (auto iter = m_pObject->GetMushRoom().begin(); iter != m_pObject->GetMushRoom().end(); ++iter)
	{
		if (IntersectRect(&ct, &RectMakeCenter(BprobeX, BprobeY, 40, 2), &RectMake(iter->PosX - (m_pMap->GetMoveX() + 5), iter->PosY, 40, 50)))
		{
			smallJump = true;
			iter->isDie = true;
		}
		else if (IntersectRect(&ct, &RectMakeCenter(RprobeX, RprobeY, 2, 20), &RectMake(iter->PosX - (m_pMap->GetMoveX() + 5), iter->PosY, 40, 50)))
		{
			if (isGiant)
			{
				int posx = m_pPlayerImage->GetPosX();
				int posy = m_pPlayerImage->GetPosY();
				m_pPlayerImage = g_pImageManager->FindImage("MarioRight");
				m_pPlayerImage->SetPosX(posx);
				m_pPlayerImage->SetPosY(posy);
			}
			else
				isDie = true;
		}
		else if (IntersectRect(&ct, &RectMakeCenter(LprobeX, LprobeY, 2, 20), &RectMake(iter->PosX - (m_pMap->GetMoveX() + 5), iter->PosY, 40, 50)))
		{
			if (isGiant)
			{
				int posx = m_pPlayerImage->GetPosX();
				int posy = m_pPlayerImage->GetPosY();
				m_pPlayerImage = g_pImageManager->FindImage("MarioRight");
				m_pPlayerImage->SetPosX(posx);
				m_pPlayerImage->SetPosY(posy);
			}
			else
				isDie = true;
		}
	}

	if (smallJump)
	{
		m_pPlayerImage->SetPosY(m_fPosY - m_fEnermyJump + m_fGravity);
		m_fGravity += GRAVITY;

		if (m_fGravity > m_fEnermyJump)
		{
			BprobeY = m_pPlayerImage->GetPosY() + m_pPlayerImage->GetFrameHeight() / 2 + m_fGravity;

			if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX + m_pMap->GetMoveX(), BprobeY - 5) == false)
			{
				m_fGravity = 0.0f;
				smallJump = false;
			}
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

void cMarioPlayer::MiniRender()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	EllipseMakeCenter(g_hDC, m_pPlayerImage->GetPosX(), m_pPlayerImage->GetPosY(), 10, 10);

	DeleteObject(hSelectPen);
	DeleteObject(hPen);
}


void cMarioPlayer::Render()
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

void cMarioPlayer::SetLanding()
{
	m_fGravity = 0.0f;
	m_fJumpPower = 10.0f;
	m_isJumpping = false;
}