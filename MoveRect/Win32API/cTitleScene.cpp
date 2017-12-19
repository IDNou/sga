#include "stdafx.h"
#include "cTitleScene.h"


void cTitleScene::Setup()
{
	PosX =100;
	PosY = WINSIZEY / 2;

	isEdge = false;
	isStart = false;
	isChainge = true;
	isCalculate = false;
	isDone = true;
	isCalculateDone = false;

	saveNode = 0;
	connectNode = 0;
	currentNode = 1;
	NextNode = 0;
	arriveNode = 0;
	arriveNode2 = 0;

	count = 1;
	time = 0;
	chartSize = 0;

	POINT StartPoint = { PosX,PosY };
	Node.m_ptMousePosition = StartPoint;
	Node.m_intNodeNum = count;
	Node.via = 1;
	Node.cost = 0;
	Node.open = true;
	m_vPointPath.push_back(Node);
}

void cTitleScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown('1'))
	{
		g_pSceneManager->SetNextScene(SLIST_PLAY);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		isStart = true;
	}

	if (isStart && m_vPointPath.size() > 1 && chartSize >= 0)
	{
		if (isChainge)
		{
			/*for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); ++iter)
			{
				if (iter->m_intNodeNum == currentNode && iter->m_vNodeNumber.size() > 0)
				{
					int Random = GetRandom(iter->m_vNodeNumber.size());
					NextNode = iter->m_vNodeNumber[Random];
				}
			}*/
			NextNode = chart[chartSize - 1];

			isChainge = false;
		}

		LinearInterpolation(PosX, PosY, PosX, PosY, m_vPointPath[NextNode-1].m_ptMousePosition.x, m_vPointPath[NextNode-1].m_ptMousePosition.y, 0.1f);
		time += 0.015f;

		if (time > 1.0f)
		{
			time = 0;
			//���⿡�ٰ� ���� ���͸� �����ؾ���
			if(chartSize > 1)
				chartSize--;
			isChainge = true;
		}
	}

	if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		//�����մ°�
		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); ++iter)
		{
			if (PtInRect(&RectMakeCenter(iter->m_ptMousePosition.x, iter->m_ptMousePosition.y, 30, 30), g_ptMouse))
			{
				LinePos.PreveX = iter->m_ptMousePosition.x;
				LinePos.PreveY = iter->m_ptMousePosition.y;
				saveNode = iter->m_intNodeNum;
				isEdge = true;
			}
		}
		// ��� �߰�
		if (!isEdge)
		{
			count++;
			Node.m_ptMousePosition = g_ptMouse;
			Node.m_intNodeNum = count;
			Node.via = 0;
			Node.cost = Infinite;
			Node.open = true;
			m_vPointPath.push_back(Node);
		}
	}
	
	// ���� �ִ°� ������
	if (g_pKeyManager->isOnceKeyUp(VK_LBUTTON))
	{
		if (isEdge)
		{
			for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); ++iter)
			{
				if (PtInRect(&RectMakeCenter(iter->m_ptMousePosition.x, iter->m_ptMousePosition.y, 30, 30), g_ptMouse))
				{
					connectNode = iter->m_intNodeNum;
					if (saveNode != connectNode) 
					{
						LinePos.NextX = iter->m_ptMousePosition.x;
						LinePos.NextY = iter->m_ptMousePosition.y;
						LinePos.edgeCost = GetLength(LinePos.PreveX, LinePos.PreveY, LinePos.NextX, LinePos.NextY);
						LinePos.PreveIndex = saveNode;
						LinePos.NextIndex = iter->m_intNodeNum;
						m_vLinePos.push_back(LinePos);
						iter->m_vNodeNumber.push_back(saveNode);

						for (auto iter2 = m_vPointPath.begin(); iter2 != m_vPointPath.end(); ++iter2)
						{
							if (iter2->m_intNodeNum == saveNode)
							{
								iter2->m_vNodeNumber.push_back(connectNode);
							}
						}
					}

					isEdge = false;
				}
			}
			saveNode = 0;
			connectNode = 0;
		}
	}

	if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON)) // ��Ʈ ��带 ������
	{
		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); ++iter)
		{
			if (PtInRect(&RectMakeCenter(iter->m_ptMousePosition.x, iter->m_ptMousePosition.y, 30, 30), g_ptMouse))
			{
				//���� �ؾ��ϴ� ���
				arriveNode = iter->m_intNodeNum;
				arriveNode2 = iter->m_intNodeNum;
			}
		}
		isCalculate = true;
	}

	// ����ϴ°�
	if (isCalculate)
	{
		if (CalculateDone())
		{
			isCalculate = false;
			isCalculateDone = true;
		}
	}
}

void cTitleScene::Render()
{
	char buffer[256];

	RectangleMakeCenter(g_hDC, PosX , PosY , 50, 50);

	for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); ++iter)
	{
		if (iter->m_intNodeNum == arriveNode2)
		{
			HPEN Pen = CreatePen(NULL,2,RGB(255,0,0));
			HPEN oPen = (HPEN)SelectObject(g_hDC, Pen);
			RectangleMakeCenter(g_hDC, iter->m_ptMousePosition.x, iter->m_ptMousePosition.y, 30, 30);
			SelectObject(g_hDC, oPen);
			DeleteObject(Pen);
		}
		else if (iter->m_intNodeNum == arriveNode)
		{
			HPEN Pen = CreatePen(NULL, 2, RGB(255, 0, 0));
			HPEN oPen = (HPEN)SelectObject(g_hDC, Pen);
			RectangleMakeCenter(g_hDC, iter->m_ptMousePosition.x, iter->m_ptMousePosition.y, 30, 30);
			SelectObject(g_hDC, oPen);
			DeleteObject(Pen);
		}
		else
		{
			RectangleMakeCenter(g_hDC, iter->m_ptMousePosition.x, iter->m_ptMousePosition.y, 30, 30);
			sprintf(buffer, "id:%d", iter->m_intNodeNum);
			TextOut(g_hDC, iter->m_ptMousePosition.x, iter->m_ptMousePosition.y + 10, buffer, strlen(buffer));
		}

	}
	for (auto iter = m_vLinePos.begin(); iter != m_vLinePos.end(); ++iter)
	{
		LineMake(g_hDC, iter->PreveX, iter->PreveY, iter->NextX, iter->NextY);
	}

	if (isCalculateDone)
	{
		TextOut(g_hDC, WINSIZEX - 200, 100, "�ى�", strlen("�ى�"));
	}
}

void cTitleScene::Release()
{
	
}

bool cTitleScene::CalculateDone()
{
	int LowCost = Infinite;
	int	index = 0;

	while (isDone)
	{
		LowCost = Infinite;

		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); iter++)
		{
			cout << iter->m_intNodeNum << " " << iter->via << " " << iter->cost << " " << iter->open << endl;
		}

		//���µ� ����� ���� ���� �ڽ�Ʈ�� ���� ��带 ����
		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); iter++)
		{
			if (iter->open && LowCost > iter->cost)
			{
				LowCost = iter->cost;
				index = iter->m_intNodeNum;
			}
		}

		//����
		//���ŵ� ����� �θ���
		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); iter++)
		{
			if(index == iter->m_intNodeNum)
			{
				// �׳��ӿ� ����Ǿ��ִ� ��带 ã��
				for (auto iter2 = iter->m_vNodeNumber.begin(); iter2 != iter->m_vNodeNumber.end(); iter2++)
				{
					// ����� ��� ����
					for (auto iter3 = m_vPointPath.begin(); iter3 != m_vPointPath.end(); iter3++)
					{
						if (iter3->open && *iter2 == iter3->m_intNodeNum)
						{
							//�ڽ�Ʈ ����
							for (auto iter4 = m_vLinePos.begin(); iter4 != m_vLinePos.end(); iter4++)
							{
								if (iter4->NextIndex == iter3->m_intNodeNum && iter->m_intNodeNum == iter4->PreveIndex)
									if (iter3->via == 0)
									{
										iter3->cost = iter->cost + iter4->edgeCost;
										iter3->via = iter->m_intNodeNum;
									}
									else if (iter3->via > 0)
									{
										if (iter3->cost > iter->cost + iter4->edgeCost)
										{
											iter3->cost = iter->cost + iter4->edgeCost;
											iter3->via = iter->m_intNodeNum;
										}
									}
								if (iter4->PreveIndex == iter3->m_intNodeNum && iter->m_intNodeNum == iter4->NextIndex)
									if (iter3->via == 0)
									{
										iter3->cost = iter->cost + iter4->edgeCost;
										iter3->via = iter->m_intNodeNum;
									}
									else if (iter3->via > 0)
									{
										if (iter3->cost > iter->cost + iter4->edgeCost)
										{
											iter3->cost = iter->cost + iter4->edgeCost;
											iter3->via = iter->m_intNodeNum;
										}
									}
							}
						}
					}
				}
				iter->open = false;
			}
		}

		
		//�� Ŭ���� ����� üũ
		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); iter++)
		{
			if (iter->open)
			{
				isDone = true;
				break;
			}
			else
			{
				isDone = false;
			}
		}
	}

	//��Ʈ �״°�
	chart.push_back(arriveNode);
	while (1)
	{
		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); ++iter)
		{
			if (iter->m_intNodeNum == arriveNode)
			{
				arriveNode = iter->via;
				chart.push_back(iter->via);
			}
		}

		if (arriveNode == 1)
			break;
	}

	chartSize = chart.size();

	return true;
}

