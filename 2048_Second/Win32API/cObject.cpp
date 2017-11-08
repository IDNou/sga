#include "stdafx.h"
#include "cObject.h"
#include "cMap.h"
#include "cPlayer.h"


cObject::cObject()
{
	BlockWidth = Width;
	BlockHeight = Height;
	overRap = false;
}


cObject::~cObject()
{
}

void cObject::Setup()
{
	for (int i = 0; i < 16; i++)
	{
		SetNum[i] = i;
	}

	for (int i = 0; i < 1000; i++)
	{
		int dest = rand() % 16;
		int sour = rand() % 16;
		int tmp = 0;
		
		tmp = SetNum[dest];
		SetNum[dest] = SetNum[sour];
		SetNum[sour] = tmp;
	}

	for (int i = 0; i < 2; i++)
	{
	/*	block.PosX = 110 + (SetNum[i] % 4 * 125);
		block.PosY = 300 + (SetNum[i] / 4 * 108);*/
		block.PosX = 110 + ((2) * Width);
		block.PosY = 300 + (i * Height);
		block.uId = 3+(i*4);
		//block.uId = SetNum[i]+1;
		block.isExist = true;
		if (rand() % 10 < 8)
		{
			block.Number = 2;
			block.m_pImageBlock = g_pImageManager->FindImage("2");
		}
		else
		{
			block.Number = 4;
			block.m_pImageBlock = g_pImageManager->FindImage("4");
		}
		vecBlock.push_back(block);
	}
		
	//vecBlock.push_back(block);
		
	
}

void cObject::Update()
{
	if (m_pPlayer->GetIsCreate())
	{
		if (vecBlock.size() < 16)
		{
			int createRand = rand() % 16;
			
			while (1)
			{
				overRap = false;
				for (auto iter = vecBlock.begin(); iter != vecBlock.end(); ++iter)
				{
					if (iter->uId == createRand + 1)
					{
						createRand = rand() % 16;
						overRap = true;
						break;
					}
				}
				if (!overRap)
					break;
			}

			block.PosX = 110 + (createRand % 4 * 125);
			block.PosY = 300 + (createRand / 4 * 108);
			block.uId = createRand + 1;
			block.isExist = true;
			if (rand() % 10 < 8)
			{
				block.Number = 2;
				block.m_pImageBlock = g_pImageManager->FindImage("2");
			}
			else
			{
				block.Number = 4;
				block.m_pImageBlock = g_pImageManager->FindImage("4");
			}
			vecBlock.push_back(block);
		}
		m_pPlayer->SetIsCreate(false);
	}
	cout << vecBlock.size() << endl;
}

void cObject::Render()
{
	for (auto iter = vecBlock.begin(); iter != vecBlock.end(); ++iter)
	{
		//RectangleMakeCenter(g_hDC, iter->PosX, iter->PosY, 100, 100);
		iter->m_pImageBlock->Render(g_hDC, iter->PosX - 50, iter->PosY - 50, 0, 0, 100, 100);
	}
}
