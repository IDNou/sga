#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;

class cMainGame : public cGameNode
{
private:
	bool			m_isPlaying;

	cImage*			m_pImgBackground;		// 화면 전체 배경
	cImage*			m_pImgMiniMap;			// 미니맵용 이미지 버퍼
	cImage*			m_pImgMapBuffer;		// 지형 지물이 그려진 맵 버퍼

	cMap*			m_pMap;
	cPlayer*		m_pPlayer;

	int				PosX;
	int				PosY;
	int				savePosX;
	int				savePosY;

	void LoadImageFromFile();
	void MiniMapRender();

public:
	cMainGame();
	~cMainGame();

	void Setup();
	virtual void Update() override;
	virtual void Render() override;

	void SetPosX(int x) { PosX = x; }
	void SetPosY(int y) { PosY = y; }
};