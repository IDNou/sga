#include "stdafx.h"
#include "cPlayScene.h"


void cPlayScene::Setup()
{
	// 모든 칸을 0으로 초기화
	for (int i = 0; i < 16; ++i)
		m_nValue[i / 4][i % 4] = 0;

	// 랜덤한 위치에 2 또는 4를 생성
	m_nValue[GetRandom(4)][GetRandom(4)] = GetRandom(1, 2);

	m_pImgNumbers = g_pImageManager->FindImage("numbers");
}

void cPlayScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
		g_pSceneManager->ChangeScene(SLIST_LOADING);

	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->ChangeScene(SLIST_TITLE);
	}

	DIRECTION dir = WAIT;
	bool move = false;

	if (g_pKeyManager->isOnceKeyDown(VK_LEFT))
		dir = LEFT;
	else if (g_pKeyManager->isOnceKeyDown(VK_RIGHT))
		dir = RIGHT;
	else if (g_pKeyManager->isOnceKeyDown(VK_UP))
		dir = UP;
	else if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
		dir = DOWN;

	if (dir != WAIT)
	{
		Move(move, dir);
		Merge(move, dir);
		Move(move, dir);
		NewNumber(move);
	}
}

void cPlayScene::Render()
{
	char szBuf[8];
	char* str;

	for (int i = 0; i < 16; ++i)
	{
		RectangleMakeCenter(g_hDC, 100 * (i % 4) + 100, 100 * (i / 4) + 200, 100, 100);

		//int sourX = 100 * (log2(m_nValue[i / 4][i % 4]) - 1);

		//if (m_nValue[i / 4][i % 4] != 0)
		//	m_pImgNumbers->Render(g_hDC, 100 * (i % 4) + 50, 100 * (i / 4) + 150,
		//		sourX, 0, 100, 100);

		if (m_nValue[i / 4][i % 4] != 0)
			m_pImgNumbers->Render(g_hDC, 100 * (i % 4) + 50, 100 * (i / 4) + 150,
				100 * (m_nValue[i / 4][i % 4] - 1), 0, 100, 100);
	}
}

void cPlayScene::Release()
{
}

void cPlayScene::Move(bool& move, DIRECTION dir)
{
	for (int k = 0; k < 3; ++k)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				switch (dir)
				{
				case cPlayScene::LEFT:
					MoveBlock(move, m_nValue[i][j], m_nValue[i][j + 1]);
					//if (m_nValue[i][j] == 0)
					//{
					//	m_nValue[i][j] = m_nValue[i][j + 1];
					//	m_nValue[i][j + 1] = 0;
					//	move = true;
					//}
					break;
				case cPlayScene::RIGHT:
					MoveBlock(move, m_nValue[i][3 - j], m_nValue[i][3 - (j + 1)]);
					break;
				case cPlayScene::UP:
					MoveBlock(move, m_nValue[j][i], m_nValue[j + 1][i]);
					break;
				case cPlayScene::DOWN:
					MoveBlock(move, m_nValue[3 - j][i], m_nValue[3 - (j + 1)][i]);
					break;
				}
			}
		}
	}
}

void cPlayScene::MoveBlock(bool& move, int& dest, int& origin)
{
	if (dest == 0 && origin != 0)
	{
		dest = origin;
		origin = 0;
		move = true;
	}
}

void cPlayScene::NewNumber(const bool move)
{
	if (move == false) return;

	int i, j;

	do
	{
		i = GetRandom(4);
		j = GetRandom(4);
	} while (m_nValue[i][j] != 0);

	m_nValue[i][j] = GetRandom(1, 2) * 2;
}

void cPlayScene::Merge(bool& move, DIRECTION dir)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			switch (dir)
			{
			case cPlayScene::LEFT:
				MergeBlock(move, m_nValue[i][j], m_nValue[i][j + 1]);
				break;
			case cPlayScene::RIGHT:
				MergeBlock(move, m_nValue[i][3 - j], m_nValue[i][3 - (j + 1)]);
				break;
			case cPlayScene::UP:
				MergeBlock(move, m_nValue[j][i], m_nValue[j + 1][i]);
				break;
			case cPlayScene::DOWN:
				MergeBlock(move, m_nValue[3 - j][i], m_nValue[3 - (j + 1)][i]);
				break;
			}
		}
	}
}

void cPlayScene::MergeBlock(bool& move, int& dest, int& origin)
{
	if (dest != 0 && dest == origin)
	{
		dest += 1;
		origin = 0;
		move = true;
	}
}