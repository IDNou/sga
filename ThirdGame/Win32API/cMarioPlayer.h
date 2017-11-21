#pragma once

class cProgressBar;
class cMarioMap;
class cMarioObject;

#define MAP1_Y (WINSIZEY - 110)

class cMarioPlayer
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
	float			m_fEnermyJump;
	bool			isDie;
	bool			smallJump;
	bool			isGiant;

	int				m_nMapYPos;			// �÷��̾��� �ٴ��� ���� (�ʿ� ���� �ٸ��� ������ �ʿ�)
	int				m_nDamageDelay;		// ���� ������ ������ ������(���� ���)

	cImage*			m_pMapImg;			// ��� ���� �̹���

	cMarioMap*			m_pMap;
	cMarioObject*		m_pObject;

public:
	cMarioPlayer();
	~cMarioPlayer();

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
	void SetMap(cMarioMap* map) { m_pMap = map; }
	void SetObject(cMarioObject * object) { m_pObject = object; }
	void SetLanding();
#pragma endregion
};

