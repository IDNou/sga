#include "stdafx.h"
#include "cMainGame.h"

// �� ������ϵ� �߰�
#include "cTitleScene.h"
#include "cPlayScene.h"
#include "cLoadingScene.h"
#include "cDijkstraTest.h"
#include "cMapTool.h"
#include "cWaterPathScene.h"
#include "cSetupInfo.h"
#include "cHouseScene.h"
#include "cBossScene.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
}

void cMainGame::Setup()
{

	ifstream File_Item;
	File_Item.open("ItemList.json");
	File_Item >> ItemList;
	File_Item.close();

	json ImageList;
	ifstream File_Image;
	File_Image.open("ImageList.json");
	File_Image >> ImageList;
	File_Image.close();

	isPause = false;

	//������ �̹��� �߰�
	for (int j = 0; j < ImageList["Image"].size(); j++)
	{
		string RouteName = ImageList["Image"][j]["ROUTE"];

		g_pImageManager->AddImage(ImageList["Image"][j]["NAME"],
			RouteName.c_str(),
			ImageList["Image"][j]["WIDTH"],
			ImageList["Image"][j]["HEIGHT"],
			true,
			RGB(255, 0, 255));
	}

	//������ �߰�
	for (int i = 0; i < ItemList["Item"].size(); i++)
	{
		g_pItemManager->ItemAdd(ItemList["Item"][i]["NAME"],
			g_pImageManager->FindImage(ItemList["Item"][i]["NAME"]),
			(ItemType)ItemList["Item"][i]["TYPE"],
			ItemList["Item"][i]["ATK"],
			ItemList["Item"][i]["DEF"],
			ItemList["Item"][i]["HP"],
			ItemList["Item"][i]["PRICE"]);
	}

	// �� �߰�
	g_pSceneManager->AddScene(SLIST_LOADING, new cLoadingScene);
	g_pSceneManager->AddScene(SLIST_TITLE, new cTitleScene);
	g_pSceneManager->AddScene(SLIST_MAPTOOL, new cMapTool);
	g_pSceneManager->AddScene(SLIST_PLAY, new cPlayScene);
	g_pSceneManager->AddScene(SLIST_PLAY2, new cDijkstraTest);
	g_pSceneManager->AddScene(SLIST_WATERPATH, new cWaterPathScene);
	g_pSceneManager->AddScene(SLIST_HOUSE, new cHouseScene);
	g_pSceneManager->AddScene(SLIST_BOSSMAP, new cBossScene);

	// ó�� ���� �� ����
	g_pSceneManager->ChangeScene(SLIST_LOADING);

	g_pPlayerManager->Start();

	//�κ��� �������� ������ ����
	g_pPlayerManager->GetPlayer()->GetPlayerInven().push_back(g_pItemManager->FindItem("ManaSword"));
	g_pPlayerManager->GetPlayer()->GetPlayerInven().push_back(g_pItemManager->FindItem("Candy"));


	// ������ �̸����
	
	SetupInfo = new cSetupInfo;


}

void cMainGame::Update()
{
	cGameNode::Update();

	if (!isPause)
		g_pSceneManager->Update();
	else
		SetupInfo->Update();

	if (g_pKeyManager->isOnceKeyDown('P'))
	{
		if (!isPause)
		{
			isPause = true;
			SetupInfo->Setup();
		}
		else
		{
			isPause = false;
			SetupInfo->Release();
		}
	}
}

void cMainGame::Render()
{
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(g_hWnd, &ps);

	// ������� �̹����� ĥ�Ѵ�.
	PatBlt(g_hDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (!isPause)
		g_pSceneManager->Render();
	else
		SetupInfo->Render();
	g_pTimeManager->Render();
	m_pImgBackBuffer->Render(hdc);

	EndPaint(g_hWnd, &ps);
}

void cMainGame::Release()
{
	g_pKeyManager->ReleaseInstance();
	g_pFileData->ReleaseInstance();
	g_pPixelManager->ReleaseInstance();
	g_pTimeManager->ReleaseInstance();
	g_pIniData->ReleaseInstance();
	g_pImageManager->ReleaseInstance();
	g_pSceneManager->ReleaseInstance();
	g_pSoundManager->ReleaseInstance();
}
