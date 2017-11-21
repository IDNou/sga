#pragma once
#include "cGameNode.h"

#define DELAY 6

class cJumakScene : public cGameNode
{
private:
	int MaxX = 40;
	int MaxY = 30;
	cTile*         m_pJumakTile;
	tagTile		   JumakTile[40][30];

	cImage*			m_pPlayBuffer;
	int				m_nPosX;
	int				m_nPosY;
	RECT			m_rtPlayer;
	int				m_nMoveDelay;
	RECT			m_rtViewPort;
public:
	cJumakScene();
	virtual ~cJumakScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	
};

