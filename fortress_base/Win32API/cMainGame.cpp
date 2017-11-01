#include "stdafx.h"
#include "cMainGame.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cObjects.h"


cMainGame::cMainGame()
	: m_isPlaying(false)
{
	LoadImageFromFile();

	m_pMap = new cMap;
	m_pPlayer = new cPlayer;
	m_pObject = new cObjects;
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void cMainGame::Setup()
{
	m_pMap->Setup();
	m_pMap->SetPlayer(m_pPlayer);
	m_pMap->SetObject(m_pObject);
	m_pPlayer->Setup();
	m_pPlayer->SetMap(m_pMap);
	m_pPlayer->SetObject(m_pObject);
	m_pObject->Setup();
	m_pObject->SetPlayer(m_pPlayer);
	m_pObject->SetMap(m_pMap);
}

void cMainGame::Update()
{
	cGameNode::Update();

	if (m_isPlaying)
	{
		m_pMap->Update();
		m_pPlayer->Update();
		m_pObject->Update();
	}
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
	{
		Setup();
		m_isPlaying = true;
	}
}

void cMainGame::Render()
{
	// ������� �̹����� ĥ�Ѵ�.
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

void cMainGame::LoadImageFromFile()
{
	/* ��ü ��� */
	g_pImageManager->AddImage("Map", "images/paladin.bmp", 3750, 3000, true, RGB(255, 0, 255));

	/* �� */
	//g_pImageManager->AddImage("Map_Magenta", "images/marioBackground_magenta.bmp", 8000, 600, true, RGB(255, 0, 255));
	g_pImageManager->AddImage("MapBuffer", WINSIZEX, WINSIZEY)->SetTransColor(true, RGB(255, 0, 255));

	/* �̴ϸ� */
	m_pImgMiniMap = g_pImageManager->AddImage("MiniMap", WINSIZEX, WINSIZEY / 5);

	/* ���α׷����� */
	

	/* ������ ������Ʈ*/
	

	/* �÷��̾� */
	

	/* ���� */
	

	/* ������ */
	

}

void cMainGame::MiniMapRender()
{
	//m_pImgBackgoround = g_pImageManager->FindImage("Map");
	//m_pBufferMinimap = g_pImageManager->FindImage("Map");
	//m_pPlayer->MiniRender();
	
	//PatBlt(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5, BLACKNESS);
	//m_pImgBackgoround->Render(m_pImgMiniMap->GetMemDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgBackgoround->GetFrameHeight());
	//m_pBufferMinimap->AlphaRender(m_pImgMiniMap->GetMemDC(), 0, 0, WINSIZEX, WINSIZEY / 5, 64); // ���� �̴ϸ�
	//m_backBuffer->Render(m_pImgMiniMap->GetMemDC(), m_pMap->GetMoveX() / (m_pBufferMinimap->GetFrameWidth() / WINSIZEX), 0,
	//	WINSIZEX/(m_pBufferMinimap->GetFrameWidth() / WINSIZEX), WINSIZEY / 5); // �̴ϸ� ������
	//m_pImgMiniMap->Render(g_hDC, 0, 0);
}