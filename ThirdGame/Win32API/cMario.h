#pragma once
#include "cGameNode.h"

class cMarioMap;
class cMarioPlayer;
class cMarioObject;

class cMario : public cGameNode
{
private:
	bool			m_isPlaying;

	cMarioMap*			m_pMap;
	cMarioObject*		m_pObject;
	cMarioPlayer*		m_pPlayer;
	cImage*			m_pImgMiniMap;			// 미니맵용 이미지 버퍼
	cImage*			m_pBufferMinimap;
	cImage*			m_pImgBackgoround;

	void MiniMapRender();
	void LoadImageFromFile();

public:
	cMario() {};
	virtual ~cMario() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

