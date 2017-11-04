#pragma once

class cPlayer;

class cMap
{
private:
	cImage*		m_pImgMap;			// �⺻ ���� �̹���(����Ÿ�� �ִ� ���� ����)
	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����
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