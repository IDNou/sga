#pragma once

class c2048Player;
class c2048Object;

class c2048Map
{
private:
	cImage*		m_pImgMap;			// 기본 지형 이미지(마젠타가 있는 지형 파일)
	cImage*		m_pImgMapBuffer;	// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼

	c2048Player*	m_pPlayer;
	c2048Object*	m_pObject;

public:
	c2048Map();
	~c2048Map();

	void Setup();
	void Update();
	void Render();

	void SetPlayer(c2048Player* player) { m_pPlayer = player; }
	void SetObject(c2048Object* object) { m_pObject = object; }
};