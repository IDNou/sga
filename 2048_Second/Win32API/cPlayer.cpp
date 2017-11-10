#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"
#include "cObject.h"


cPlayer::cPlayer()
{
	isCreate = false;
	isExist = false;
	isNotExist = false;
	iterCount = 0;
	lastCount = 0;
	SumCount = 0;
	SumCount2 = 0;
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
		m_pObject->SetVecEqual(m_pObject->GetVecBlock());

		SumCount = 0;

		for (auto iter = m_pObject->GetVecEqual().begin(); iter != m_pObject->GetVecEqual().end(); iter++)
		{
			if (iter->isExist)
				SumCount += iter->uId;
		}
		cout << SumCount << endl;

		for (int i = 2; i >= 0; i--)
		{
			for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end(); ++iter)
			{
				if (iter->isExist && iter->uId % 4 == i)
				{
					for (int j = 1; j < 4 - i; j++)
					{
						if ((iter + j)->isExist) // 앞에 존재를 한다면
						{
							if ((iter + j)->Number == iter->Number)// 합치는거
							{
								char buffer[256];
								(iter + j)->Number *= 2;
								sprintf(buffer, "%d", (iter + j)->Number);
								//(iter + j)->m_pImageBlock = g_pImageManager->FindImage(buffer);
								(iter + j)->m_pImageBlock = g_pImageManager->FindImage("Number");

								iter->Number = 0;
								iter->isExist = false;
								break;
							}
							else // 숫자가 같지않을때 앞으로 가지말아야함
							{
								isExist = true;
								iterCount = j - 1;
								break;
							}
						}

						if (j == 3 - i)
						{
							isNotExist = true;
							lastCount = j;
						}
					}

					if (isExist)
					{
						isExist = false;
						if (iterCount != 0)
						{
							(iter + iterCount)->isExist = true;
							(iter + iterCount)->Number = iter->Number;
							(iter+iterCount)->m_pImageBlock = iter->m_pImageBlock;

							iter->Number = 0;
							iter->isExist = false;
							iter->m_pImageBlock = NULL;
						}
					}

					if (isNotExist)
					{
						(iter + lastCount)->isExist = true;
						(iter + lastCount)->Number = iter->Number;
						(iter + lastCount)->m_pImageBlock = iter->m_pImageBlock;

						iter->isExist = false;
						iter->Number = 0;
						iter->m_pImageBlock = NULL;
						isNotExist = false;
						lastCount = 0;
					}
				}
			}
		}

		SumCount2 = 0;
		for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end(); iter++)
		{
			if (iter->isExist)
				SumCount2 += iter->uId;
		}
		cout << SumCount2 << endl;
		
		if(SumCount != SumCount2)
			isCreate = true;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_LEFT))
	{
		m_pObject->SetVecEqual(m_pObject->GetVecBlock());

		SumCount = 0;

		for (auto iter = m_pObject->GetVecEqual().begin(); iter != m_pObject->GetVecEqual().end(); iter++)
		{
			if (iter->isExist)
				SumCount += iter->uId;
		}
		cout << SumCount << endl;

		for (int i = 1; i <= 3; i++)
		{
			for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end(); ++iter)
			{
				if (iter->isExist && iter->uId % 4 == i)
				{
					for (int j = 1; j < i+1; j++)
					{
						if ((iter - j)->isExist) // 앞에 존재를 한다면
						{
							if ((iter - j)->Number == iter->Number)// 합치는거
							{
								char buffer[256];
								(iter - j)->Number *= 2;
								sprintf(buffer, "%d", (iter - j)->Number);
								//(iter - j)->m_pImageBlock = g_pImageManager->FindImage(buffer);
								(iter - j)->m_pImageBlock = g_pImageManager->FindImage("Number");

								iter->Number = 0;
								iter->isExist = false;
								break;
							}
							else // 숫자가 같지않을때 앞으로 가지말아야함
							{
								isExist = true;
								iterCount = j - 1;
								break;
							}
						}

						if (j == i)
						{
							isNotExist = true;
							lastCount = -j;
						}
					}

					if (isExist)
					{
						isExist = false;
						if (iterCount != 0)
						{
							(iter - iterCount)->isExist = true;
							(iter - iterCount)->Number = iter->Number;
							(iter - iterCount)->m_pImageBlock = iter->m_pImageBlock;

							iter->Number = 0;
							iter->isExist = false;
							iter->m_pImageBlock = NULL;

							iterCount = 0;
						}
					}

					if (isNotExist)
					{
						(iter + lastCount)->isExist = true;
						(iter + lastCount)->Number = iter->Number;
						(iter + lastCount)->m_pImageBlock = iter->m_pImageBlock;

						iter->isExist = false;
						iter->Number = 0;
						iter->m_pImageBlock = NULL;
						isNotExist = false;
						lastCount = 0;
					}
				}
			}
		}

		SumCount2 = 0;
		for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end(); iter++)
		{
			if (iter->isExist)
				SumCount2 += iter->uId;
		}
		cout << SumCount2 << endl;

		if (SumCount != SumCount2)
			isCreate = true;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		m_pObject->SetVecEqual(m_pObject->GetVecBlock());

		SumCount = 0;

		for (auto iter = m_pObject->GetVecEqual().begin(); iter != m_pObject->GetVecEqual().end(); iter++)
		{
			if (iter->isExist)
				SumCount += iter->uId;
		}
		cout << SumCount << endl;

		for (int i = 1; i < 4; i++)
		{
			for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end(); ++iter)
			{
				if (iter->uId / 4 == i && iter->isExist)
				{
					for (int j = 1; j < i + 1; j++)
					{
						if ((iter - (j * 4))->isExist) // 앞에 존재를 한다면
						{
							if ((iter - (j * 4))->Number == iter->Number)// 합치는거
							{
								char buffer[256];
								(iter - (j * 4))->Number *= 2;
								sprintf(buffer, "%d", (iter - (j * 4))->Number);
								//(iter - (j * 4))->m_pImageBlock = g_pImageManager->FindImage(buffer);
								(iter - (j * 4))->m_pImageBlock = g_pImageManager->FindImage("Number");

								iter->Number = 0;
								iter->isExist = false;
								break;
							}
							else // 숫자가 같지않을때 앞으로 가지말아야함
							{
								isExist = true;
								iterCount = (j - 1)*4;
								break;
							}
						}

						if (j == i)
						{
							isNotExist = true;
							lastCount = j * 4;
						}
					}

					if (isExist)
					{
						isExist = false;
						if (iterCount != 0)
						{
							(iter - iterCount)->isExist = true;
							(iter - iterCount)->Number = iter->Number;
							(iter - iterCount)->m_pImageBlock = iter->m_pImageBlock;

							iter->Number = 0;
							iter->isExist = false;
							iter->m_pImageBlock = NULL;

							iterCount = 0;
						}
					}

					if (isNotExist)
					{
						(iter - lastCount)->isExist = true;
						(iter - lastCount)->Number = iter->Number;
						(iter - lastCount)->m_pImageBlock = iter->m_pImageBlock;

						iter->isExist = false;
						iter->Number = 0;
						iter->m_pImageBlock = NULL;
						isNotExist = false;
						lastCount = 0;
					}
				}
			}
		}

		SumCount2 = 0;
		for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end(); iter++)
		{
			if (iter->isExist)
				SumCount2 += iter->uId;
		}
		cout << SumCount2 << endl;

		if (SumCount != SumCount2)
			isCreate = true;
	}

	else if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		m_pObject->SetVecEqual(m_pObject->GetVecBlock());

		SumCount = 0;

		for (auto iter = m_pObject->GetVecEqual().begin(); iter != m_pObject->GetVecEqual().end(); iter++)
		{
			if (iter->isExist)
				SumCount += iter->uId;
		}
		cout << SumCount << endl;

		for (int i = 2; i >= 0; i--)
		{
			for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end(); ++iter)
			{
				if (iter->isExist && iter->uId / 4 == i)
				{
					for (int j = 1; j < 4 - i; j++)
					{
						if ((iter + (j * 4))->isExist) // 앞에 존재를 한다면
						{
							if ((iter + (j * 4))->Number == iter->Number)// 합치는거
							{
								char buffer[256];
								(iter + (j * 4))->Number *= 2;
								sprintf(buffer, "%d", (iter + (j * 4))->Number);
								//(iter + (j * 4))->m_pImageBlock = g_pImageManager->FindImage(buffer);
								(iter + (j * 4))->m_pImageBlock = g_pImageManager->FindImage("Number");

								iter->Number = 0;
								iter->isExist = false;
								break;
							}
							else // 숫자가 같지않을때 앞으로 가지말아야함
							{
								isExist = true;
								iterCount = (j - 1)*4;
								break;
							}
						}

						if (j == 3 - i)
						{
							isNotExist = true;
							lastCount = j * 4;
						}
					}

					if (isExist)
					{
						isExist = false;
						if (iterCount != 0)
						{
							(iter + iterCount)->isExist = true;
							(iter + iterCount)->Number = iter->Number;
							(iter + iterCount)->m_pImageBlock = iter->m_pImageBlock;

							iter->Number = 0;
							iter->isExist = false;
							iter->m_pImageBlock = NULL;
						}
					}

					if (isNotExist)
					{
						(iter + lastCount)->isExist = true;
						(iter + lastCount)->Number = iter->Number;
						(iter + lastCount)->m_pImageBlock = iter->m_pImageBlock;

						iter->isExist = false;
						iter->Number = 0;
						iter->m_pImageBlock = NULL;
						isNotExist = false;
						lastCount = 0;
					}
				}
			}
		}

		SumCount2 = 0;
		for (auto iter = m_pObject->GetVecBlock().begin(); iter != m_pObject->GetVecBlock().end(); iter++)
		{
			if (iter->isExist)
				SumCount2 += iter->uId;
		}
		cout << SumCount2 << endl;

		if (SumCount != SumCount2)
			isCreate = true;
	}
}

void cPlayer::Render()
{
	HPEN hPen = (HPEN)CreatePen(0, 3, RGB(255, 0, 0));
	HPEN hSelectPen = (HPEN)SelectObject(g_hDC, hPen);

	DeleteObject(hSelectPen);
	DeleteObject(hPen);
}