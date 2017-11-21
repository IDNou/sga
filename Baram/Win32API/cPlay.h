#pragma once
#include "cGameNode.h"
class cPlay : public cGameNode
{
private:
	//UI �̹��� ===============

	cImage*		m_CursorImage;

	cImage*		m_Mainframe;
	cImage*		m_MainState;
	cImage*		m_State1;
	cImage*		m_State2;
	cImage*		m_MainItem;
	cImage*		m_MainSkill;
	cImage*		m_MainLevel;
	cImage*		m_MainHP;

	//=========================
	//��ư �浹ó�� ��Ʈ========

	RECT		rt_MainState;
	RECT		rt_State1;
	RECT		rt_State2;
	RECT		rt_MainItem;
	RECT		rt_MainSkill;
	RECT		rt_On_Off;

	//=========================
	//��ư �浹ó�� �Ұ�========

	bool		m_isMainState;
	bool		m_isState1;
	bool		m_isState2;
	bool		m_isOn_Off;
	bool		m_isMainItem;
	bool		m_isMainSkill;

	//=========================

public:
	cPlay() {};
	virtual ~cPlay() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

