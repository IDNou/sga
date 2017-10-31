#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
{
	m_pImgBackgoround = g_pImageManager->FindImage("Map");
	m_pImgGround = g_pImageManager->FindImage("Map_Magenta");
	m_pImgDraw = g_pImageManager->FindImage("fill");
	m_pImgMagenta = g_pImageManager->FindImage("magenta");
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

	for (int i = 0; i < 5; ++i)
	{
		wall.PosX = 1035 + (i * 41);
		wall.PosY = 365;
		wall.isBreak = false;
		if (i == 2) {
			wall.type = eMushRoomBox;
			wall.MushRoomItemNum = 1;
		}
		else
		{
			wall.type = eBox;
			wall.MushRoomItemNum = 0;
		}
		vecWall.push_back(wall);
	}

	for (int i = 0; i < 11; ++i)
	{
		wall.PosX = 2315 + (i * 41);
		wall.PosY = 365;
		wall.isBreak = false;
		wall.type = eWall;
		wall.MushRoomItemNum = 0;
		vecWall.push_back(wall);
	}

	for (int i = 0; i < 14; ++i)
	{
		wall.PosX = 2235 + (i * 41);
		wall.PosY = 200;
		wall.isBreak = false;
		wall.type = eWall;
		wall.MushRoomItemNum = 0;
		vecWall.push_back(wall);
	}

	for (int i = 0; i < 18; ++i)
	{
		if (i == 4)
			continue;
		wall.PosX = 2915 + (i * 41);
		wall.PosY = 200;
		wall.isBreak = false;
		wall.type = eWall;
		wall.MushRoomItemNum = 0;
		vecWall.push_back(wall);
	}

	for (int i = 0; i < 6; ++i)
	{
		wall.PosX = 4995 + (i * 41);
		wall.PosY = 200;
		wall.isBreak = false;
		wall.type = eWall;
		wall.MushRoomItemNum = 0;
		vecWall.push_back(wall);
	}
}

void cMap::Update()
{
	/*if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
	{
		g_pPixelManager->RemoveBrush(m_pImgGround, g_ptMouse.x, g_ptMouse.y, 40);
		g_pPixelManager->RemoveBrush(m_pImgBackgoround, g_ptMouse.x, g_ptMouse.y, 40);
	}*/
	/*if (g_pKeyManager->isStayKeyDown(VK_RBUTTON)) {
		g_pPixelManager->DrawImage(m_pImgGround, m_pImgMagenta, g_ptMouse.x + moveBackgrounX, g_ptMouse.y, 40, 40);
		g_pPixelManager->DrawImage(m_pImgBackgoround, m_pImgMagenta, g_ptMouse.x + moveBackgrounX, g_ptMouse.y, 40, 40);
	}*/

	for (auto iter = vecWall.begin(); iter != vecWall.end();)
	{
		if (iter->isBreak)
		{
			g_pPixelManager->DrawImage(m_pImgGround, m_pImgMagenta, iter->PosX, iter->PosY, 42, 44);
			g_pPixelManager->DrawImage(m_pImgBackgoround, m_pImgDraw, iter->PosX, iter->PosY, 42, 44);
			iter = vecWall.erase(iter);
		}
		else
			++iter;
	}
}

void cMap::Render()
{

	m_pImgBackgoround->Render(g_hDC, 0, 0, moveBackgrounX, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgBackgoround->GetFrameHeight());
	m_pImgGround->Render(g_hDC, 0, 0, moveBackgrounX, 0, WINSIZEX, WINSIZEY, WINSIZEX, m_pImgGround->GetFrameHeight());

#ifdef _DEBUG
	for (auto iter = vecWall.begin(); iter != vecWall.end(); ++iter)
	{
		RectangleMake(g_hDC, iter->PosX - moveBackgrounX, iter->PosY, 40, 40);
	}
#endif

	// string 문자열 클래스 : 문자열에 대한 연산자 사용이 가능하다 ex) +=
	string str("맵 X 좌표 : ");
	char szStr[128];
	//str += "asdfasdfsadf";
	str += itoa(m_nSourX, szStr, 10); // itoa => 인트형을 문자열로 변환 (변환 소스, 임시 저장소, 숫자의 진수)
	TextOutA(g_hDC, 100, 100, str.c_str(), str.length());
}