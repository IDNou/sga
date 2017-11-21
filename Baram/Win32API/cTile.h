#pragma once

class cTile 
{
private:

	
	cImage*			m_pPlayBuffer;
	int				m_nPosX;
	int				m_nPosY;
	RECT			m_rtPlayer;
	int				m_nMoveDelay;
	RECT			m_rtViewPort;
public:
	cTile();
	virtual ~cTile();


	tagTile CreateDefaultTiles(int x, int y);
	tagTile SettingTiles(int AlphaHeight = 0, int AlphaVolume = 0, bool isMove = true);
	bool SettingTilesNoMove();
	bool SettingTilesMove();


};

