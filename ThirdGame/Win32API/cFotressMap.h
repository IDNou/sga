#pragma once

class cFotressPlayer;

class cFotressMap
{
private:
	cImage*		m_pImgMap;			// �⺻ ���� �̹���(����Ÿ�� �ִ� ���� ����)
	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����
	cImage*		m_pImgBackground;

	cFotressPlayer*	m_pPlayer;

	int			PosX;
	int			PosY;

public:
	cFotressMap();
	~cFotressMap();

	void Setup();
	void Update();
	void Render();

#pragma region Set
	void SetPlayer(cFotressPlayer* player) { m_pPlayer = player; }
#pragma endregion

#pragma region Get
	int	GetMapWidth() { return m_pImgMap->GetWidth(); }
	int	getMapHeight() { return m_pImgMap->GetHeight(); }
#pragma endregion
};