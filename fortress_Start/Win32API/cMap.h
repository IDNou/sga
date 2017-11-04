#pragma once

class cPlayer;

class cMap
{
private:
	cImage*		m_pImgMap;			// 기본 지형 이미지(마젠타가 있는 지형 파일)
	cImage*		m_pImgMapBuffer;	// 최종적으로 픽셀 충돌을 위해서 만들어질 지형 이미지 버퍼
	cImage*		m_pImgBackground;

	cPlayer*	m_pPlayer;

	int			PosX;
	int			PosY;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

#pragma region Set
	void SetPlayer(cPlayer* player) { m_pPlayer = player; }
#pragma endregion

#pragma region Get
	int	GetMapWidth() { return m_pImgMap->GetWidth(); }
	int	getMapHeight() { return m_pImgMap->GetHeight(); }
#pragma endregion
};