#include "stdafx.h"
#include "cPlayScene.h"
#include "cMap.h"
#include "cPlayer.h"

cPlayScene::cPlayScene()
{
}


cPlayScene::~cPlayScene()
{
}

void cPlayScene::Setup()
{
	LoadImageFromFile();

	m_pMap = new cMap;
	m_pMap->Setup();

	m_pPlayer = new cPlayer;
	m_pPlayer->Setup();

	m_pMap->SetPlayer(m_pPlayer);
	m_pPlayer->SetMap(m_pMap);
}

void cPlayScene::Update()
{
	m_pMap->Update();
	m_pPlayer->Update();

	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->ChangeScene("Title");
	}
}

void cPlayScene::Render()
{
	m_pImgBackground->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);

	m_pMap->Render();
	m_pPlayer->Render();

}

void cPlayScene::Release()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void cPlayScene::LoadImageFromFile()
{
	/* ��ü ��� */
	m_pImgBackground = g_pImageManager->AddImage("OmokPan", "images/omokbg.bmp", 1000, 800, true, RGB(255, 0, 255));

	/* �� */
	
	/* �̴ϸ�(�� ��Ʈ��) - ���� �� �������� 1/5 ������� �����. */
	

	/* ������Ʈ */
	g_pImageManager->AddImage("Stone", "images/omok.bmp", 54, 108, 1, 2, true, RGB(255, 0, 255));

	/* �÷��̾� */
	
}