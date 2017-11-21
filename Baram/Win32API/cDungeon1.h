#pragma once
#include "cGameNode.h"
#define DELAY 6

class cDungeon1 : public cGameNode
{
	int MaxX = 27;
	int MaxY = 18;
	cTile*         m_pDungeonTile;
	tagTile		   DungeonTile[27][18];

	cImage*			m_pPlayBuffer;
	int				m_nPosX;
	int				m_nPosY;
	RECT			m_rtPlayer;
	RECT			m_rtTop;
	RECT			m_rtBottom;
	RECT			m_rtLeft;
	RECT			m_rtRight;

	int				m_nMoveDelay;
	RECT			m_rtViewPort;
	RECT			Error;
public:
	cDungeon1();
	virtual ~cDungeon1();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void LoadingImage();
};

