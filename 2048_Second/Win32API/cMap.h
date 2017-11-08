#pragma once

class cPlayer;
class cObject;

class cMap
{
private:
	cImage*		m_pImgMap;			// 기본 지형 이미지(마젠타가 있는 지형 파일)
	cImage*		m_pImgMapBuffer;	// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼

	cPlayer*	m_pPlayer;
	cObject*	m_pObject;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	void SetPlayer(cPlayer* player) { m_pPlayer = player; }
	void SetObject(cObject* object) { m_pObject = object; }
};