#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;
class cObject;

class cPlayScene : public cGameNode
{
private:
	cImage*			m_pImgBackground;		// ȭ�� ��ü ���
	cImage*			m_pImgMiniMap;			// �̴ϸʿ� �̹��� ����
	cImage*			m_pImgMapBuffer;		// ���� ������ �׷��� �� ����

	cMap*			m_pMap;
	cPlayer*		m_pPlayer;
	cObject*		m_pObject;

	void LoadImageFromFile();
	void MiniMapRender();

public:
	cPlayScene();
	virtual ~cPlayScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

