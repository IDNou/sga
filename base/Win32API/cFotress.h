#pragma once
#include "cGameNode.h"

class cFotressMap;
class cFotressPlayer;

class cFotress : public cGameNode
{
private:
	bool			m_isPlaying;

	cImage*			m_pImgBackground;		// 화면 전체 배경
	cImage*			m_pImgMiniMap;			// 미니맵용 이미지 버퍼
	cImage*			m_pImgMapBuffer;		// 지형 지물이 그려진 맵 버퍼

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

