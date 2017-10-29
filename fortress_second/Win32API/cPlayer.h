#pragma once

class cProgressBar;
class cMap;
class cObjects;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;		// 플레이어 이미지 파일
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

	float			m_fGravity;			// 중력 (점프시 사용)
	bool			m_isJumpping;		// 점프 중이냐?
	float			m_fJumpPower;		// 점프 파워
	bool			isDie;

	int				m_nMapYPos;			// 플레이어의 바닥위 설정 (맵에 따라 다르게 설정이 필요)
	int				m_nDamageDelay;		// 연속 데미지 방지용 딜레이(무적 모드)

	cImage*			m_pMapImg;			// 배경 정보 이미지

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

