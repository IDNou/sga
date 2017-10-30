#include "stdafx.h"
#include "cObjects.h"
#include "cPlayer.h"
#include "cMap.h"
#include "cProgressBar.h"


cObjects::cObjects()
{
	m_pMushRoom = g_pImageManager->FindImage("MushRoom");

	m_pMapImg = g_pImageManager->FindImage("Map_Magenta");
}

cObjects::~cObjects()
{
}

void cObjects::Setup()
{
	moveGroundX = 0;
	framecount = 20;

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

	for (auto iter = vecMushRoom.begin(); iter != vecMushRoom.end();)
	{
		if (iter->isDie)
			iter = vecMushRoom.erase(iter);
		else
			++iter;
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

		m_pMushRoom->FrameRender(g_hDC, iter->PosX - moveGroundX, iter->PosY, m_pMushRoom->GetFrameX(), m_pMushRoom->GetFrameY());
	}
}