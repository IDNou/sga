#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"


cPlayer::cPlayer()
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	alretColor = 0;

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			Stone.isActivity = false;
			Stone.stoneUID = i * 13 + j;
			Stone.stoneColor = 2;
			Stone.stoneImage =NULL;
			Stone.PosX = (j * 54) + 75 - 27;
			Stone.PosY = (i * 54) + 75 - 27;
			vecStone.push_back(Stone);
		}
	}
}

void cPlayer::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{

		RECT rt;
		for (auto iter = vecStone.begin(); iter != vecStone.end(); iter++)
		{
			if (PtInRect(&RectMake(iter->PosX, iter->PosY, 54, 54), g_ptMouse))
			{
				if (!iter->isActivity)
				{
					iter->isActivity = true;
					iter->stoneColor = alretColor % 2;
					iter->stoneImage = g_pImageManager->FindImage("Stone");
					alretColor++;
					break;
				}
			}
		}
		// 오목인지 아닌지 검사하는 알고리즘

	}
}

void cPlayer::Render()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	

	DeleteObject(hSelectPen);
	DeleteObject(hPen);
}