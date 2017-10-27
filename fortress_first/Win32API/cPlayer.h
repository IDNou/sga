#pragma once

class cProgressBar;
class cMap;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;		// �÷��̾� �̹��� ����
	float			m_fPosX;
	float			m_fPosY;

	float			m_fGravity;			// �߷� (������ ���)
	bool			m_isJumpping;		// ���� ���̳�?
	float			m_fJumpPower;		// ���� �Ŀ�

	int				m_nMapYPos;			// �÷��̾��� �ٴ��� ���� (�ʿ� ���� �ٸ��� ������ �ʿ�)
	int				m_nDamageDelay;		// ���� ������ ������ ������(���� ���)

	cProgressBar*	m_pHpBar;
	float			m_fMaxHp;
	float			m_fCurrHp;

	cImage*			m_pMapImg;			// ��� ���� �̹���

	cMap*			m_pMap;

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void MiniRender();
	void Render();

#pragma region Get
	RECT GetBoundingBox() { return m_pPlayerImage->GetBoundingBox(); }
	float GetPosX() { return m_pPlayerImage->GetPosX(); }
	float GetPosY() { return m_pPlayerImage->GetPosY(); }
	int GetDamageDelay() { return m_nDamageDelay; }
#pragma endregion

#pragma region Set
	void SetDamageDelay(int delay) { m_nDamageDelay = delay; }
	void SetMap(cMap* map) { m_pMap = map; }
	void SetLanding();
#pragma endregion
};

