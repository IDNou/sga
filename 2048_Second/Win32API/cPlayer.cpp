#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"
#include "cObject.h"


cPlayer::cPlayer()
{
	isSame = false;
	isCreate = false;
	isExist = false;
}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
}

void cPlayer::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_RIGHT))
	{
		isCreate = true;
		
		// 3��°���� ������
		for (int i = 3; i > 0; --i)
		{
			for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end(); ++iter)
			{
				// 3��°�� ���ͺ��� ���ʴ�� ã�Ƴ�
				if (iter->uId % 4 == i) 
				{
					for (auto iter2 = m_pObject->GetVecBlock().begin(); iter2 != m_pObject->GetVecBlock().end(); ++iter2)
					{

						for (int j = i; j < 4; j++)
						{
							if (iter->uId + (4 - j) == iter2->uId)
							{
								isExist = true;
								if (iter->Number == iter2->Number)
								{
									isSame = true;
									char buffer[256];
									iter->isExist = false;
									iter2->Number *= 2;
									sprintf(buffer, "%d", iter2->Number);
									iter2->m_pImageBlock = g_pImageManager->FindImage(buffer);
								}
							}
						}

						////�տ� ���Ͱ� �����ϴ°�. �˻���
						//if (iter->uId + (4 - i) == iter2->uId) // �� 4��° �ִ� ��ϸ� �˻��ع���. 
						//{
						//	isExist = true;
						//	if (iter->Number == iter2->Number)
						//	{
						//		isSame = true;
						//		char buffer[256];
						//		iter->isExist = false;
						//		iter2->Number *= 2;
						//		sprintf(buffer, "%d", iter2->Number);
						//		iter2->m_pImageBlock = g_pImageManager->FindImage(buffer);
						//	}
						//}
						
					}

					/*if (!isExist && !isSame)
					{
						iter->PosX += m_pObject->GetBlockWidth();
						iter->uId += 1;
					}
					isSame = false;
					isExist = false;*/
				}
			}
		}
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_LEFT))
	{

	}
	else if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{

	}
	else if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{

	}

	for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end();)
	{
		if (iter->isExist == false)
			iter = m_pObject->GetVecBlock().erase(iter);
		else
			++iter;
	}
}

void cPlayer::Render()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	DeleteObject(hSelectPen);
	DeleteObject(hPen);
}