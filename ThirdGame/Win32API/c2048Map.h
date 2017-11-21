#pragma once

class c2048Player;
class c2048Object;

class c2048Map
{
private:
	cImage*		m_pImgMap;			// �⺻ ���� �̹���(����Ÿ�� �ִ� ���� ����)
	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����

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