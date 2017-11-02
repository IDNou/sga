#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;

class cMainGame : public cGameNode
{
private:
	bool			m_isPlaying;

	cImage*			m_pImgBackground;		// ȭ�� ��ü ���
	cImage*			m_pImgMiniMap;			// �̴ϸʿ� �̹��� ����
	cImage*			m_pImgMapBuffer;		// ���� ������ �׷��� �� ����

	cMap*			m_pMap;
	cPlayer*		m_pPlayer;

	void LoadImageFromFile();
	void MiniMapRender();

public:
	cMainGame();
	~cMainGame();

	void Setup();
	virtual void Update() override;
	virtual void Render() override;
};