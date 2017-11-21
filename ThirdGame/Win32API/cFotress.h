#pragma once
#include "cGameNode.h"

class cFotressMap;
class cFotressPlayer;

class cFotress : public cGameNode
{
private:
	bool			m_isPlaying;

	cImage*			m_pImgBackground;		// ȭ�� ��ü ���
	cImage*			m_pImgMiniMap;			// �̴ϸʿ� �̹��� ����
	cImage*			m_pImgMapBuffer;		// ���� ������ �׷��� �� ����

	cFotressMap*			m_pMap;
	cFotressPlayer*		m_pPlayer;

	int				PosX;
	int				PosY;
	int				savePosX;
	int				savePosY;

	void LoadImageFromFile();
	void MiniMapRender();
public:
	cFotress() {};
	virtual ~cFotress() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

