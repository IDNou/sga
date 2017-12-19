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
			//여기에다가 다음 벡터를 결정해야함
			if(chartSize > 1)
				chartSize--;
			isChainge = true;
		}
	}

	if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		//간선잇는거
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
		// 노드 추가
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
	
	// 간선 있는거 도착점
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

	if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON)) // 라스트 노드를 정해줌
	{
		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); ++iter)
		{
			if (PtInRect(&RectMakeCenter(iter->m_ptMousePosition.x, iter->m_ptMousePosition.y, 30, 30), g_ptMouse))
			{
				//도착 해야하는 노드
				arriveNode = iter->m_intNodeNum;
				arriveNode2 = iter->m_intNodeNum;
			}
		}
		isCalculate = true;
	}

	// 계산하는거
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
		TextOut(g_hDC, WINSIZEX - 200, 100, "다됌", strlen("다됌"));
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

		//오픈된 노드중 가장 작은 코스트를 가진 노드를 선택
		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); iter++)
		{
			if (iter->open && LowCost > iter->cost)
			{
				LowCost = iter->cost;
				index = iter->m_intNodeNum;
			}
		}

		//갱신
		//갱신될 노드의 부모노드
		for (auto iter = m_vPointPath.begin(); iter != m_vPointPath.end(); iter++)
		{
			if(index == iter->m_intNodeNum)
			{
				// 그노드속에 연결되어있는 노드를 찾음
				for (auto iter2 = iter->m_vNodeNumber.begin(); iter2 != iter->m_vNodeNumber.end(); iter2++)
				{
					// 연결된 노드 갱신
					for (auto iter3 = m_vPointPath.begin(); iter3 != m_vPointPath.end(); iter3++)
					{
						if (iter3->open && *iter2 == iter3->m_intNodeNum)
						{
							//코스트 갱신
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

		
		//다 클로즈 됬는지 체크
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

	//차트 쌓는곳
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

