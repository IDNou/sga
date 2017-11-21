#include "stdafx.h"
#include "cMario.h"
#include "cMarioMap.h"
#include "cMarioPlayer.h"
#include "cMarioObject.h"

void cMario::Setup()
{
	m_isPlaying = false;

	LoadImageFromFile();

	m_pMap = new cMarioMap;
	m_pPlayer = new cMarioPlayer;
	m_pObject = new cMarioObject;

	m_pMap->Setup();
	m_pPlayer->Setup();
	m_pPlayer->SetMap(m_pMap);
	m_pPlayer->SetObject(m_pObject);
	m_pObject->Setup();
	m_pObject->SetPlayer(m_pPlayer);
	m_pObject->SetMap(m_pMap);
}

void cMario::Update()
{
	if (m_isPlaying)
	{
		m_pMap->Update();
		m_pPlayer->Update();
		m_pObject->Update();

		if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		{
			m_isPlaying = false;
		}

		if (m_pPlayer->GetIsDie())
			m_isPlaying = false;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		Setup();
		m_isPlaying = true;
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
}

void cMario::Render()
{
	// Èò»öÀ¸·Î ÀÌ¹ÌÁö¸¦ Ä¥ÇÑ´Ù.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (m_isPlaying)
	{
		m_pMap->Render();
		MiniMapRender();
		m_pPlayer->Render();
		m_pObject->Render();
	}
	else
	{
		TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, "Enter to Start", strlen("Enter to Start"));
	}
}

void cMario::Release()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void cMario::LoadImageFromFile()
{
	
	g_pImageManager->AddEmptyImage("MapBuffer", WINSIZEX, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

	/* ¹Ì´Ï¸Ê */
	m_pImgMiniMap = g_pImageManager->AddEmptyImage("MiniMap", WINSIZEX, WINSIZEY / 5);

}

void cMario::MiniMapRender()
{
	m_pBufferMinimap = g_pImageManager->FindImage("Map");
	m_pImgBackgoround = g_pImageManager->FindImage("Map");
	m_pPlayer->MiniRender();
	
	//PatBlt(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5, BLACKNESS);
	m_pImgBackgoround->Render(m_pImgMiniMap->GetMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgBackgoround->GetFrameHeight());
	m_pBufferMinimap->AlphaRender(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5, 64); // ¾ËÆÄ ¹Ì´Ï¸Ê
	m_pImgBackBuffer->Render(m_pImgMiniMap->GetMemDC(), m_pMap->GetMoveX() / (m_pBufferMinimap->GetFrameWidth() / WINSIZEX), 0,
		WINSIZEX/(m_pBufferMinimap->GetFrameWidth() / WINSIZEX), WINSIZEY / 5); // ¹Ì´Ï¸Ê ÃßÀû±â
	m_pImgMiniMap->Render(g_hDC, 0, 0);
}