#include "stdafx.h"
#include "cObjects.h"
#include "cPlayer.h"
#include "cMap.h"
#include "cProgressBar.h"


cObjects::cObjects()
{
	m_pMushRoom = g_pImageManager->FindImage("MushRoom");
	m_pMapImg = g_pImageManager->FindImage("Map_Magenta");
	m_pItemMushRoom = g_pImageManager->FindImage("ItemMushRoom");
	m_pMoveBar = g_pImageManager->FindImage("bar");
	m_pFlower = g_pImageManager->FindImage("Flower");
}

cObjects::~cObjects()
{
}

void cObjects::Setup()
{
	moveGroundX = 0;
	framecount = 20;

	sct_MushRoomItem.PosX = 1115;
	sct_MushRoomItem.PosY = 325;
	sct_MushRoomItem.objMushRoomItemNum = 1;
	sct_MushRoomItem.isActiveMushRoomItem = false;
	sct_MushRoomItem.dir = RIGHT;
	sct_MushRoomItem.isDie = false;
	vecMushRoomItem.push_back(sct_MushRoomItem);

	/*sct_MushRoomItem.PosX = 3560;
	sct_MushRoomItem.PosY = 325;
	sct_MushRoomItem.objMushRoomItemNum = 2;
	sct_MushRoomItem.isActiveMushRoomItem = false;
	sct_MushRoomItem.dir = RIGHT;
	sct_MushRoomItem.isDie = false;
	vecMushRoomItem.push_back(sct_MushRoomItem);*/

	sct_MushRooom.PosX =1300;
	sct_MushRooom.PosY = 480;
	sct_MushRooom.isDie = false;
	sct_MushRooom.dir = LEFT;
	vecMushRoom.push_back(sct_MushRooom);

	sct_MushRooom.PosX = 2500;
	sct_MushRooom.PosY = 480;
	sct_MushRooom.isDie = false;
	sct_MushRooom.dir = LEFT;
	vecMushRoom.push_back(sct_MushRooom);

	sct_MushRooom.PosX = 4200;
	sct_MushRooom.PosY = 480;
	sct_MushRooom.isDie = false;
	sct_MushRooom.dir = LEFT;
	vecMushRoom.push_back(sct_MushRooom);

	sct_MushRooom.PosX = 4300;
	sct_MushRooom.PosY = 480;
	sct_MushRooom.isDie = false;
	sct_MushRooom.dir = LEFT;
	vecMushRoom.push_back(sct_MushRooom);
}

void cObjects::Update()
{
	if(framecount <0)
	{
		framecount = 20;
		m_pMushRoom->SetFrameX(m_pMushRoom->GetFrameX() + 1);
	}
	if (m_pMushRoom->GetFrameX() > m_pMushRoom->GetMaxFrameX())
		m_pMushRoom->SetFrameX(0);

	for (auto iter = vecMushRoom.begin(); iter != vecMushRoom.end(); ++iter)
	{
		BprobeX = iter->PosX + 20;
		BprobeY = iter->PosY + 50;

		LprobeX = iter->PosX;
		LprobeY = iter->PosY + 25;

		RprobeX = iter->PosX + 40;
		RprobeY = iter->PosY + 25;


		if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX, BprobeY))
			iter->PosY += 5;
		else if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX, BprobeY -5) == false)
			iter->PosY -= 5;
		

		if (BprobeY >= 600 || iter->PosX <= 0)
			iter->isDie = true;
		

		if (g_pPixelManager->CheckPixel(m_pMapImg, LprobeX, LprobeY) == false)
			iter->dir = RIGHT;
		
		else if (g_pPixelManager->CheckPixel(m_pMapImg, RprobeX, RprobeY) == false)
			iter->dir = LEFT;
		

		if (iter->dir == LEFT)
			iter->PosX -= 1;
		else if (iter->dir == RIGHT)
			iter->PosX += 1;
	}
	//버섯 적 삭제
	for (auto iter = vecMushRoom.begin(); iter != vecMushRoom.end();)
	{
		if (iter->isDie)
			iter = vecMushRoom.erase(iter);
		else
			++iter;
	}

	for (auto iter = vecMushRoomItem.begin(); iter != vecMushRoomItem.end(); )
	{
		if (iter->isDie)
			iter = vecMushRoomItem.erase(iter);
		else
			++iter;
	}

	//바움직임
	m_pMoveBar->SetPosX(m_pMoveBar->GetPosX() + 1);

	//아이템 버섯 움직임
	for (auto iter = vecMushRoomItem.begin(); iter != vecMushRoomItem.end(); ++iter)
	{

		BprobeX = iter->PosX + 20;
		BprobeY = iter->PosY + 40;
		LprobeX = iter->PosX;
		LprobeY = iter->PosY + 25;
		RprobeX = iter->PosX + 40;
		RprobeY = iter->PosY + 25;

		if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX, BprobeY))
			iter->PosY += 5;
		else if (g_pPixelManager->CheckPixel(m_pMapImg, BprobeX, BprobeY - 5) == false)
			iter->PosY -= 5;

		if (iter->isActiveMushRoomItem)
		{
			if (g_pPixelManager->CheckPixel(m_pMapImg, LprobeX, LprobeY) == false)
				iter->dir = RIGHT;

			else if (g_pPixelManager->CheckPixel(m_pMapImg, RprobeX, RprobeY) == false)
				iter->dir = LEFT;

			if (iter->dir == LEFT)
				iter->PosX -= 2;
			else if (iter->dir == RIGHT)
				iter->PosX += 2;
		}
	}

	--framecount;
}

void cObjects::Render()
{
	for (auto iter = vecMushRoom.begin(); iter != vecMushRoom.end(); ++iter)
	{

		HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
		HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

		BoudingLineMake(g_hDC, iter->PosX - moveGroundX,
			iter->PosY,
			40,
			50);

		DeleteObject(hSelectPen);
		DeleteObject(hPen);
#ifdef _DEBUG
		RectangleMake(g_hDC, iter->PosX - moveGroundX, iter->PosY, 40, 50);
#endif // DEBUG

		m_pMushRoom->FrameRender(g_hDC, iter->PosX - moveGroundX, iter->PosY, m_pMushRoom->GetFrameX(), m_pMushRoom->GetFrameY());
	}

	for (auto iter = vecMushRoomItem.begin(); iter != vecMushRoomItem.end(); ++iter)
	{
		if (iter->isActiveMushRoomItem)
		{
			m_pItemMushRoom->Render(g_hDC, iter->PosX - moveGroundX, iter->PosY);
			//RectangleMake(g_hDC, iter->PosX - moveGroundX, iter->PosY, 37, 40);
		}
	}

	m_pMoveBar->Render(g_hDC,m_pMoveBar->GetPosX() + m_pMoveBar->GetFrameWidth()/2 -moveGroundX,m_pMoveBar->GetPosY());

#ifdef _DEBUG
	RectangleMake(g_hDC, m_pMoveBar->GetPosX() + m_pMoveBar->GetFrameWidth() / 2 - moveGroundX, m_pMoveBar->GetPosY(), m_pMoveBar->GetWidth(), m_pMoveBar->GetHeight());
#endif // DEBUG
}