#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;

class cPlayScene : public cGameNode
{
private:
	cImage*			m_pImgBackground;		// ȭ�� ��ü ���

	cMap*			m_pMap;
	cPlayer*		m_pPlayer;

	void LoadImageFromFile();

public:
	cPlayScene();
	virtual ~cPlayScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

