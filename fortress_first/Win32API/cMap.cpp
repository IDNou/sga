#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
{
	m_pImgBackgoround = g_pImageManager->FindImage("Map");
	m_pImgGround = g_pImageManager->FindImage("Map_Magenta");
	m_pImgDraw = g_pImageManager->FindImage("Ball");
}

cMap::~cMap()
{
}

void cMap::Setup()
{
	m_SlowSpeedDealy = 0;
	m_nSourX = 0;
	m_nMoveSpeed = 5;
	moveBackgrounX = 0;
}

void cMap::Update()
{
	if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 50);
	else if (g_pKeyManager->isStayKeyDown(VK_RBUTTON))
		g_pPixelManager->DrawImage(m_pImgGround, m_pImgDraw, g_ptMouse.x, g_ptMouse.y, 60, 60);
}

void cMap::Render()
{

	m_pImgBackgoround->Render(g_hDC, 0, 0, moveBackgrounX, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgBackgoround->GetFrameHeight());
	m_pImgGround->Render(g_hDC, 0, 0, moveBackgrounX, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgGround->GetFrameHeight());

	// string ���ڿ� Ŭ���� : ���ڿ��� ���� ������ ����� �����ϴ� ex) +=
	string str("�� X ��ǥ : ");
	char szStr[128];
	//str += "asdfasdfsadf";
	str += itoa(m_nSourX, szStr, 10); // itoa => ��Ʈ���� ���ڿ��� ��ȯ (��ȯ �ҽ�, �ӽ� �����, ������ ����)
	TextOutA(g_hDC, 100, 100, str.c_str(), str.length());
}