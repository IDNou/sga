#pragma once

class cProgressBar;
class cMap;
class cObjects;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;		// �÷��̾� �̹��� ����
	float			m_fPosX;
	float			m_fPosY;

	float			BprobeX;
	float			BprobeY;
	float			LprobeX;
	float			LprobeY;
	float			RprobeX;
	float			RprobeY;
	float			TprobeX;
	float			TprobeY;

	int				frameCount;

	float			m_fGravity;			// �߷� (������ ���)
	bool			m_isJumpping;		// ���� ���̳�?
	float			m_fJumpPower;		// ���� �Ŀ�
	bool			isDie;

	int				m_nMapYPos;			// �÷��̾��� �ٴ��� ���� (�ʿ� ���� �ٸ��� ������ �ʿ�)
	int				m_nDamageDelay;		// ���� ������ ������ ������(���� ���)

	cImage*			m_pMapImg;			// ��� ���� �̹���

	cMap*			m_pMap;
	cObjects*		m_pObject;

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
	bool GetIsDie() { return isDie; }
#pragma endregion

#pragma region Set
	void SetDamageDelay(int delay) { m_nDamageDelay = delay; }
	void SetMap(cMap* map) { m_pMap = map; }
	void SetObject(cObjects * object) { m_pObject = object; }
	void SetLanding();
#pragma endregion
};

