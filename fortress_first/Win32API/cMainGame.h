#pragma once
#include "cGameNode.h"

class cMap;
class cPlayer;

class cMainGame : public cGameNode
{
private:
	bool			m_isPlaying;

	cMap*			m_pMap;
	cPlayer*		m_pPlayer;
	cImage*			m_pImgMiniMap;			// 미니맵용 이미지 버퍼
	cImage*			m_pBufferMinimap;
	cImage*			m_pImgBackgoround;

	void LoadImageFromFile();
	void MiniMapRender();

public:
	cMainGame();
	~cMainGame();

	void Setup();
	virtual void Update() override;
	virtual void Render() override;
};