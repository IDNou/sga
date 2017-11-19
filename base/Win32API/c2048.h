#pragma once
#include "cGameNode.h"

class c2048Map;
class c2048Player;
class c2048Object;

class c2048 : public cGameNode
{
private:
	cImage*			m_pImgBackground;		// ȭ�� ��ü ���
	cImage*			m_pImgMiniMap;			// �̴ϸʿ� �̹��� ����
	cImage*			m_pImgMapBuffer;		// ���� ������ �׷��� �� ����

	c2048Map*			m_pMap;
	c2048Player*		m_pPlayer;
	c2048Object*		m_pObject;

	bool			m_isPlaying;

	void LoadImageFromFile();

public:
	c2048() {};
	virtual ~c2048() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void SetPlay(bool play) { m_isPlaying = play; }
};

