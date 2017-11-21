#pragma once
#include "cGameNode.h"

class cTitleScene :	public cGameNode
{
private:
	//메인화면 이미지 ==========

	cImage*		m_MainImage;
	cImage*		m_CursorImage;
	cImage*		m_CharacterScreen;
	cImage*		m_Select;

	//=========================
	//메인화면 버튼 충돌처리 렉트

	RECT		rt_Start;
	RECT		rt_Load;
	RECT		rt_Staff;
	RECT		rt_Exit;

	//케릭 선택창 렉트

	RECT		rt_SelectCharacter1;
	RECT		rt_SelectCharacter2;
	RECT		rt_SelectCharacter3;
	RECT		rt_SelectDone;
	RECT		rt_SelectCancel;

	//=========================
	//충돌처리 렉트 불값

	bool m_isCharacterScreen; // 처음하기 온오프
	bool m_isCharacter1;      // 캐릭 1 2 3
	bool m_isCharacter2;
	bool m_isCharacter3;

	//=========================
public:
	cTitleScene() {};
	virtual ~cTitleScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

