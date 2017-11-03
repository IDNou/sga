#pragma once

class cPlayer;

class cMap
{
private:
	cImage*		m_pImgMap;			// �⺻ ���� �̹���(����Ÿ�� �ִ� ���� ����)
	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����
	cImage*		m_pImgBackground;

	cPlayer*	m_pPlayer;

	float		m_fPosX;			// �� �̵���
	float		m_fPosY;			// �� �̵���
	float		m_fPlayerX;
	float		m_fPlayerY;

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
	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
#pragma endregion
};