#pragma once
#include "cGameNode.h"
#define DELAY 6


class cVillageScene : public cGameNode
{
private:
	tagTile			VillageTile[75][75];
	cImage*			m_pPlayBuffer;
	int				m_nPosX;
	int				m_nPosY;
	RECT			m_rtPlayer;
	int				m_nMoveDelay;
	RECT			m_rtViewPort;

public:
	cVillageScene();
	virtual ~cVillageScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;


};

