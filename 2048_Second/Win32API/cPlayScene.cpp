#include "stdafx.h"
#include "cPlayScene.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cObject.h"

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

	m_pObject = new cObject;
	m_pObject->Setup();

	m_pMap->SetPlayer(m_pPlayer);
	m_pMap->SetObject(m_pObject);
	m_pPlayer->SetMap(m_pMap);
	m_pPlayer->SetObject(m_pObject);
	m_pObject->SetMap(m_pMap);
	m_pObject->SetPlayer(m_pPlayer);
}

void cPlayScene::Update()
{
	m_pMap->Update();
	m_pPlayer->Update();
	m_pObject->Update();

	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->ChangeScene("Title");
	}
}

void cPlayScene::Render()
{
	m_pImgBackground->Render(g_hDC, 0, 0, 0, 0, WINSIZEX, WINSIZEY);

	m_pMap->Render();
	m_pObject->Render();
	m_pPlayer->Render();

	//MiniMapRender();

	/*char* str = g_pIniData->LoadDataString("ClassData", "�����", "�ּ�ȣ");
	TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2 - 50, str, strlen(str));

	int age = g_pIniData->LoadDataInteger("ClassData", "�����", "�ֵ�ö");
	char szBuf[128];
	str = itoa(age, szBuf, 10);
	TextOut(g_hDC, WINSIZEX / 2 - 200, WINSIZEY / 2, str, strlen(str));*/
}

void cPlayScene::Release()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pMap);
}

void cPlayScene::LoadImageFromFile()
{
	/* ��ü ��� */
	m_pImgBackground = g_pImageManager->AddImage("BackGround", "images/2048bg.bmp", 600, 720);

	/* �� */

	/* �̴ϸ�(�� ��Ʈ��) - ���� �� �������� 1/5 ������� �����. */

	/* ���α׷����� */

	/* ������Ʈ */
	g_pImageManager->AddImage("2", "images/2.bmp", 100, 100);
	g_pImageManager->AddImage("4", "images/4.bmp", 100, 100);
	g_pImageManager->AddImage("8", "images/8.bmp", 100, 100);
	g_pImageManager->AddImage("16", "images/16.bmp", 100, 100);
	g_pImageManager->AddImage("32", "images/32.bmp", 100, 100);
	g_pImageManager->AddImage("64", "images/64.bmp", 100, 100);
	g_pImageManager->AddImage("128", "images/128.bmp", 100, 100);
	g_pImageManager->AddImage("256", "images/256.bmp", 100, 100);
	g_pImageManager->AddImage("512", "images/512.bmp", 100, 100);
	g_pImageManager->AddImage("1024", "images/1024.bmp", 100, 100);
	g_pImageManager->AddImage("2048", "images/2048.bmp", 100, 100);
	g_pImageManager->AddImage("Number", "images/numbers.bmp", 1100, 100, 11, 1, true, RGB(255, 0, 255));

	/* �÷��̾� */
}

void cPlayScene::MiniMapRender()
{
	///* ��� �͵��� �̴ϸ� ������� ����ؼ� �׸���. */

	//// ����� ���� �׸���.
	//m_pImgBackground->Render(m_pImgMiniMap->GetMemDC(), 0, 0,
	//	m_pImgMiniMap->GetWidth(), m_pImgMiniMap->GetHeight());

	//// ���� ������ �׸���.
	//m_pImgMapBuffer->Render(m_pImgMiniMap->GetMemDC(), 0, 0,
	//	m_pImgMiniMap->GetWidth(), m_pImgMiniMap->GetHeight());

	//// �÷��̾� ��ġ
	//RectangleMakeCenter(m_pImgMiniMap->GetMemDC(),
	//	(m_pPlayer->GetPosX() + m_pMap->GetPosX()) / 5,
	//	(m_pPlayer->GetPosY() + m_pMap->GetPosY()) / 5,
	//	m_pPlayer->GetSizeX() / 5, m_pPlayer->GetSizeY() / 5);

	//m_pImgMiniMap->Render(g_hDC, 0, 0, WINSIZEX, WINSIZEY / 5);
}