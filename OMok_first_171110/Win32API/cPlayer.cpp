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
	saveUID = 0;
	rowCount = 0;
	colCount = 0;
	LdiagoCount = 0;
	RdiagoCount = 0;
	victoryCount = 0;

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
					m_pMap->SetTime(10.0f);
					iter->isActivity = true;
					iter->stoneColor = alretColor % 2;
					iter->stoneImage = g_pImageManager->FindImage("Stone");
					alretColor++;

					saveUID = iter->stoneUID;
					rowCount = 0;
					colCount = 0;
					LdiagoCount = 0;
					RdiagoCount = 0;

					int i = 1;
					while ((saveUID - i) / 13 == iter->stoneUID / 13 && (saveUID - i) >= 0)
					{
						if ((iter - i)->isActivity && (iter - i)->stoneColor == iter->stoneColor)
							rowCount++;
						else if (!(iter - i)->isActivity || (iter - i)->stoneColor != iter->stoneColor)
							break;
						i++;
					}

					i = 1;
					while ((saveUID + i) / 13 == iter->stoneUID / 13)
					{
						if ((iter + i)->isActivity && (iter + i)->stoneColor == iter->stoneColor)
							rowCount++;
						else if (!(iter + i)->isActivity || (iter + i)->stoneColor != iter->stoneColor)
							break;
						i++;
					}

					i = 1;
					while ((saveUID - (i * 13)) / 13 >= 0 && (saveUID - (i * 13)) >= 0)
					{
						if ((iter - (i * 13))->isActivity && (iter - (i * 13))->stoneColor == iter->stoneColor)
							colCount++;
						else if (!(iter - (i * 13))->isActivity || (iter - (i * 13))->stoneColor != iter->stoneColor)
							break;
						i++;
					}

					i = 1;
					while ((saveUID + (i * 13)) / 13 <= 12)
					{
						if ((iter + (i * 13))->isActivity && (iter + (i * 13))->stoneColor == iter->stoneColor)
							colCount++;
						else if (!(iter + (i * 13))->isActivity || (iter + (i * 13))->stoneColor != iter->stoneColor)
							break;
						i++;
					}

					i = 1;
					while ((saveUID - (i * 13) - i) / 13 >= 0 && (saveUID - (i * 13) - i) >= 0)
					{
						if ((iter - (i * 13) - i)->isActivity && (iter - (i * 13) - i)->stoneColor == iter->stoneColor)
							LdiagoCount++;
						else if (!(iter - (i * 13) - i)->isActivity || (iter - (i * 13) - i)->stoneColor != iter->stoneColor)
							break;
						i++;
					}

					i = 1;
					while ((saveUID + (i * 13) + i) / 13 <= 12)
					{
						if ((iter + (i * 13) + i)->isActivity && (iter + (i * 13) + i)->stoneColor == iter->stoneColor)
							LdiagoCount++;
						else if (!(iter + (i * 13) + i)->isActivity || (iter + (i * 13) + i)->stoneColor != iter->stoneColor)
							break;
						i++;
					}

					i = 1;
					while ((saveUID - (i * 13) + i) / 13 >= 0 && (saveUID - (i * 13) + i) >= 0)
					{
						if ((iter - (i * 13) + i)->isActivity && (iter - (i * 13) + i)->stoneColor == iter->stoneColor)
							RdiagoCount++;

						else if (!(iter - (i * 13) + i)->isActivity || (iter - (i * 13) + i)->stoneColor != iter->stoneColor)
							break;
						i++;
					}

					i = 1;
					while ((saveUID + (i * 13) - i) / 13 <= 12)
					{
						if ((iter + (i * 13) - i)->isActivity && (iter + (i * 13) - i)->stoneColor == iter->stoneColor)
							RdiagoCount++;
						else if (!(iter + (i * 13) - i)->isActivity || (iter + (i * 13) - i)->stoneColor != iter->stoneColor)
							break;
						i++;
					}
					break;
				}
			}
		}

		if (rowCount == 4 || colCount == 4 || LdiagoCount == 4 || RdiagoCount == 4)
		{
			if (alretColor % 2 == 1)
			{
				char buffer[255];
				victoryCount = g_pIniData->LoadDataInteger("OMok.ini", "Èæ", "½ÂÁ¡");
				victoryCount++;
				sprintf(buffer, "%d½Â", victoryCount);
				g_pIniData->AddData("Èæ", "½ÂÁ¡", buffer);
				g_pIniData->IniSave("OMok.ini");
			}
			else if (alretColor % 2 == 0)
			{
				char buffer[255];
				victoryCount = g_pIniData->LoadDataInteger("OMok.ini", "¹é", "½ÂÁ¡");
				victoryCount++;
				sprintf(buffer, "%d½Â", victoryCount);
				g_pIniData->AddData("¹é", "½ÂÁ¡", buffer);
				g_pIniData->IniSave("OMok.ini");
			}
			g_pSceneManager->ChangeScene("Title");
		}
	}
}

void cPlayer::Render()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	

	DeleteObject(hSelectPen);
	DeleteObject(hPen);
}