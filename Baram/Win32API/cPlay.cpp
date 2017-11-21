#include "stdafx.h"
#include "cPlay.h"

void cPlay::Setup()
{
	m_CursorImage = g_pImageManager->FindImage("Cursor");
	m_Mainframe = g_pImageManager->FindImage("Mainframe");
	m_MainState = g_pImageManager->FindImage("MainState");
	m_State1 = g_pImageManager->FindImage("State1");
	m_State2 = g_pImageManager->FindImage("State2");
	m_MainItem = g_pImageManager->FindImage("MainItem");
	m_MainSkill = g_pImageManager->FindImage("MainSkill");
	m_MainLevel = g_pImageManager->FindImage("MainLevel");
	m_MainHP = g_pImageManager->FindImage("MainHP");

	rt_MainState = RectMake(WINSIZEX - 214, 76, 20, 23);
	rt_State1 = RectMake(WINSIZEX - 472, 102, 25, 58);
	rt_State2 = RectMake(WINSIZEX - 472, 159, 25, 58);
	rt_On_Off = RectMake(WINSIZEX - 56, 313, 35, 35);
	rt_MainItem = RectMake(WINSIZEX - 214, 99, 20, 23);
	rt_MainSkill = RectMake(WINSIZEX - 214, 122, 20, 23);

	m_isMainState = true;
	m_isState1 = false;
	m_isState2 = false;
	m_isOn_Off = false;
	m_isMainItem = false;
	m_isMainSkill = false;
}

void cPlay::Update()
{
	// 타이틀 돌아가기 테스트용
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	// 렉트 충돌 랜더할 불값 수정
	// 메인 UI 불값
	if (PtInRect(&rt_MainState, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		m_isMainState = true;
		m_isMainItem = false;
		m_isMainSkill = false;
		g_pSoundManager->Play("Click_SD", 1.0f);
	}
	else if (PtInRect(&rt_MainItem, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		m_isMainState = false;
		m_isMainItem = true;
		m_isMainSkill = false;
		m_isOn_Off = false;
		g_pSoundManager->Play("Click_SD", 1.0f);
	}
	else if (PtInRect(&rt_MainSkill, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		m_isMainState = false;
		m_isMainItem = false;
		m_isMainSkill = true;
		m_isOn_Off = false;
		g_pSoundManager->Play("Click_SD", 1.0f);
	}
	// 스텟창 불값을 결정하는 불값
	if (m_isMainState && !m_isOn_Off && PtInRect(&rt_On_Off, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		m_isOn_Off = true;
		m_isState1 = true;
		g_pSoundManager->Play("Click_SD", 1.0f);
	}
	else if(m_isMainState && m_isOn_Off && PtInRect(&rt_On_Off, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		m_isOn_Off = false;
		g_pSoundManager->Play("Click_SD", 1.0f);
	}
	// 스텟창 불값
	if (m_isOn_Off && PtInRect(&rt_State1, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		m_isState1 = true;
		m_isState2 = false;
		g_pSoundManager->Play("Click_SD", 1.0f);
	}
	else if (m_isOn_Off && PtInRect(&rt_State2, g_ptMouse) && g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		m_isState1 = false;
		m_isState2 = true;
		g_pSoundManager->Play("Click_SD", 1.0f);
	}
	//클릭 사운드 테스트
	//if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON)) { g_pSoundManager->Play("Click_SD", 1.0f); }
}

void cPlay::Render()
{
	SetTextColor(g_hDC, RGB(90, 200, 120));
	TextOut(g_hDC, WINSIZEX / 2, WINSIZEY / 2, "플레이씬", strlen("플레이씬"));

	m_Mainframe->Render(g_hDC, 0, 0, WINSIZEX, WINSIZEY);
	// 메인 UI 렌더
	if (m_isMainState)
	{
		m_MainState->Render(g_hDC, WINSIZEX - 214, 76, 214, 555);
	}
	else if (m_isMainItem)
	{
		m_MainItem->Render(g_hDC, WINSIZEX - 214, 76, 214, 555);
	}
	else if (m_isMainSkill)
	{
		m_MainSkill->Render(g_hDC, WINSIZEX - 214, 76, 214, 555);
	}
	// 스텟 UI 랜더
	if (m_isOn_Off && m_isState1)
	{
		m_State1->Render(g_hDC, WINSIZEX - 472, 80, 252, 291);
	}
	else if (m_isOn_Off && m_isState2)
	{
		m_State2->Render(g_hDC, WINSIZEX - 472, 80, 252, 291);
	}

	m_MainLevel->Render(g_hDC, WINSIZEX - 216, 0, 216, 76);
	m_MainHP->Render(g_hDC, WINSIZEX - 207, 631, 207, 89);

	m_CursorImage->FrameRender(g_hDC, g_ptMouse.x, g_ptMouse.y, 0, 0, 7, 0, 5);

	//RectangleMake(g_hDC, rt_MainState);
	//RectangleMake(g_hDC, rt_State1);
	//RectangleMake(g_hDC, rt_State2);
	//RectangleMake(g_hDC, rt_MainItem);
	//RectangleMake(g_hDC, rt_MainSkill);
	//RectangleMake(g_hDC, rt_On_Off);



}

void cPlay::Release()
{
}
