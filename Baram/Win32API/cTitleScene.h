#pragma once
#include "cGameNode.h"

class cTitleScene :	public cGameNode
{
private:
	//����ȭ�� �̹��� ==========

	cImage*		m_MainImage;
	cImage*		m_CursorImage;
	cImage*		m_CharacterScreen;
	cImage*		m_Select;

	//=========================
	//����ȭ�� ��ư �浹ó�� ��Ʈ

	RECT		rt_Start;
	RECT		rt_Load;
	RECT		rt_Staff;
	RECT		rt_Exit;

	//�ɸ� ����â ��Ʈ

	RECT		rt_SelectCharacter1;
	RECT		rt_SelectCharacter2;
	RECT		rt_SelectCharacter3;
	RECT		rt_SelectDone;
	RECT		rt_SelectCancel;

	//=========================
	//�浹ó�� ��Ʈ �Ұ�

	bool m_isCharacterScreen; // ó���ϱ� �¿���
	bool m_isCharacter1;      // ĳ�� 1 2 3
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

