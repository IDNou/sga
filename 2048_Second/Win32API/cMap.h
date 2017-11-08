#pragma once

class cPlayer;
class cObject;

class cMap
{
private:
	cImage*		m_pImgMap;			// �⺻ ���� �̹���(����Ÿ�� �ִ� ���� ����)
	cImage*		m_pImgMapBuffer;	// ���������� �ȼ� �浹�� ���ؼ� ������� ���� �̹��� ����

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