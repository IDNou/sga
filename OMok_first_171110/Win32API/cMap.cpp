#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"


cMap::cMap()
{
}

cMap::~cMap()
{
}

void cMap::Setup()
{
	alphaStone = g_pImageManager->FindImage("Stone");
	time = 10;
}

void cMap::Update()
{


}

void cMap::Render()
{
	char buffer[256];

	RECT rt;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if(PtInRect(&RectMakeCenter((j * 54) + 75, (i * 54) + 75, 54, 54),g_ptMouse))
				alphaStone->AlphaRender(g_hDC, (j * 54) + 75 - 27, (i * 54) + 75 - 27, 0, m_pPlayer->GetAlretColor() % 2, 128);
		}
	}

	for (auto iter = m_pPlayer->GetVecStone().begin(); iter != m_pPlayer->GetVecStone().end(); ++iter)
	{
		if (iter->isActivity)
		{
			iter->stoneImage->FrameRender(g_hDC, iter->PosX, iter->PosY, 0, iter->stoneColor);
		}
	}

	RectangleMakeCenter(g_hDC, 900, 100, 150, 100);
	sprintf(buffer, "Time: %f", time);
	TextOut(g_hDC, 850, 100, buffer,strlen(buffer));

	if (time <= 0)
	{
		m_pPlayer->SetAlretColor(m_pPlayer->GetAlretColor() + 1);
		time = 10.0f;
	}

	time -= g_pTimeManager->GetEualTime();

	RectangleMakeCenter(g_hDC, 900, 700, 150, 100);

}