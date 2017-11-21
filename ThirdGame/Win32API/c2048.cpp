#include "stdafx.h"
#include "c2048.h"
#include "c2048Map.h"
#include "c2048Player.h"
#include "c2048Object.h"

void c2048::Setup()
{
	m_isPlaying = false;
	LoadImageFromFile();

	m_pMap = new c2048Map;
	m_pMap->Setup();

	m_pPlayer = new c2048Player;
	m_pPlayer->Setup();

	m_pObject = new c2048Object;
	m_pObject->Setup();

	m_pMap->SetPlayer(m_pPlayer);
	m_pMap->SetObject(m_pObject);
	m_pPlayer->SetMap(m_pMap);
	m_pPlayer->SetObject(m_pObject);
	m_pObject->SetMap(m_pMap);
	m_pObject->SetPlayer(m_pPlayer);
}

void c2048::Update()
{
	if (m_isPlaying) {
		m_pMap->Update();
		m_pPlayer->Update();
		m_pObject->Update();

		if (m_pObject->GetIsVictory())
			m_isPlaying = false;
	}

	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		m_isPlaying = true;
	}
}

void c2048::Render()
{
	if (m_isPlaying)
	{
		m_pImgBackground->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);

		m_pMap->Render();
		m_pObject->Render();
		m_pPlayer->Render();
	}
	else
	{
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
	}
}

void c2048::Release()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void c2048::LoadImageFromFile()
{
	/* 전체 배경 */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/2048bg.bmp", 600, 720);

	/* 맵 */

	/* 미니맵(빈 비트맵) - 원본 맵 사이즈의 1/5 사이즈로 만든다. */

	/* 프로그레스바 */

	/* 오브젝트 */

	/* 플레이어 */
}