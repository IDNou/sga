#pragma once
#include "cGameNode.h"

class c2048Map;
class c2048Player;
class c2048Object;

class c2048 : public cGameNode
{
private:
	cImage*			m_pImgBackground;		// 화면 전체 배경
	cImage*			m_pImgMiniMap;			// 미니맵용 이미지 버퍼
	cImage*			m_pImgMapBuffer;		// 지형 지물이 그려진 맵 버퍼

	c2048Map*			m_pMap;
	c2048Player*		m_pPlayer;
	c2048Object*		m_pObject;

	bool			m_isPlaying;

	void LoadImageFromFile();

public:
	c2048() {};
	virtual ~c2048() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void SetPlay(bool play) { m_isPlaying = play; }
};

