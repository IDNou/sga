#include "stdafx.h"
#include "cObject.h"
#include "cMap.h"
#include "cPlayer.h"


cObject::cObject()
{
	BlockWidth = Width;
	BlockHeight = Height;
	count = 0;
	FullCount = 0;
}


cObject::~cObject()
{
}

void cObject::Setup()
{
	for (int i = 0; i <4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			block.isExist = false;
			block.PosX = 110 + (j*Width);
			block.PosY = 300 + (i*Height);
			block.Number = 0;
			block.m_pImageBlock = NULL;
			block.uId = (i*4) + j;
			vecBlock.push_back(block);
		}
	}
		
	while (1)
	{
		int TwoRand = rand() % 16;
		for (auto iter = vecBlock.begin(); iter != vecBlock.end(); ++iter)
		{
			if (!iter->isExist && iter->uId == TwoRand)
			{
				count += 1;
				iter->isExist = true;
				if (rand() % 10 < 9)
				{
					iter->Number = 2;
					//iter->m_pImageBlock = g_pImageManager->FindImage("2");
					iter->m_pImageBlock = g_pImageManager->FindImage("Number");
				}
				else
				{
					iter->Number = 4;
					//iter->m_pImageBlock = g_pImageManager->FindImage("4");
					iter->m_pImageBlock = g_pImageManager->FindImage("Number");
				}
			}
		}

		if (count == 2)
		{
			count = 0;
			break;
		}
	}
	
}

void cObject::Update()
{
	if (m_pPlayer->GetIsCreate())
	{
		while (1)
		{
			FullCount = 0;
			for (auto iter = vecBlock.begin(); iter != vecBlock.end(); ++iter)
			{
				if (iter->isExist)
				{
					FullCount++;
				}
			}
			//cout << FullCount << endl;

			if (FullCount >= 16)
			{
				break;
			}

			int createRand = rand() % 16;
			for (auto iter = vecBlock.begin(); iter != vecBlock.end(); ++iter)
			{
				if (!iter->isExist && iter->uId == createRand)
				{
					count += 1;
					iter->isExist = true;
					if (rand() % 10 < 9)
					{
						iter->Number = 2;
						//iter->m_pImageBlock = g_pImageManager->FindImage("2");
						iter->m_pImageBlock = g_pImageManager->FindImage("Number");
					}
					else
					{
						iter->Number = 4;
						//iter->m_pImageBlock = g_pImageManager->FindImage("4");
						iter->m_pImageBlock = g_pImageManager->FindImage("Number");
					}
				}
			}

			if (count == 1)
			{
				count = 0;
				break;
			}
		}

		m_pPlayer->SetIsCreate(false);
	}

	for (auto iter = vecBlock.begin(); iter != vecBlock.end(); ++iter)
	{
		if (iter->Number == 2048)
		{
			g_pSceneManager->ChangeScene("Title");
		}
	}
}

void cObject::Render()
{
	for (auto iter = vecBlock.begin(); iter != vecBlock.end(); ++iter)
	{
		if (iter->isExist)
		{
			//iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 0, 0, 100, 100);
			switch (iter->Number)
			{
			case 2:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 0, 0, 100, 100);
				break;
			case 4:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 100, 0, 100, 100);
				break;
			case 8:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 200, 0, 100, 100);
				break;
			case 16:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 300, 0, 100, 100);
				break;
			case 32:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 400, 0, 100, 100);
				break;
			case 64:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 500, 0, 100, 100);
				break;
			case 128:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 600, 0, 100, 100);
				break;
			case 256:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 700, 0, 100, 100);
				break;
			case 512:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 800, 0, 100, 100);
				break;
			case 1024:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 900, 0, 100, 100);
				break;
			case 2048:
				iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 1000, 0, 100, 100);
				break;
			default:
				break;
			}
		}
	}
}
