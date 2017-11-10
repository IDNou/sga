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
}

void cMap::Update()
{


}

void cMap::Render()
{

	RECT rt;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (IntersectRect(&rt, &RectMakeCenter((j * 54) + 75, (i * 54) + 75, 54, 54), &RectMakeCenter(g_ptMouse.x, g_ptMouse.y, 2, 2)))
			{
				//RectangleMakeCenter(g_hDC, (j * 54) + 75, (i * 54) + 75, 54, 54);
				alphaStone->AlphaRender(g_hDC, (j * 54) + 75 - 27, (i * 54) + 75 - 27, 0, 0, 128);
			}
		}
	}

	for (auto iter = m_pPlayer->GetVecStone().begin(); iter != m_pPlayer->GetVecStone().end(); ++iter)
	{
		if (iter->isActivity)
		{
			iter->stoneImage->FrameRender(g_hDC, iter->PosX, iter->PosY, 0, iter->stoneColor);
		}
	}

}