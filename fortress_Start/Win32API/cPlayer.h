#pragma once

class cProgressBar;
class cMap;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pPlayerImage;		// 플레이어 이미지 파일

	float			m_fGravity;			// 중력 (점프시 사용)
	float			m_fMoveSpeed;		// 캐릭터 이동 스피드
	bool			m_isMapMove;		// 맵이 움직이는가?
	float			BprobeX;
	float			BprobeY;
	float			RprobeX;
	float			RprobeY;
	float			LprobeX;
	float			LprobeY;
	bool			isDie;

	cProgressBar*	m_pHpBar;
	float			m_fMaxHp;
	float			m_fCurrHp;

	cMap*			m_pMap;
	cImage*			m_pImgMapBuffer;	// 배경 정보 이미지(마젠타가 들어 있는 픽셀 충돌용 맵)

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();

#pragma region Set
	void SetMap(cMap* map) { m_pMap = map; }
#pragma endregion

#pragma region Get
	RECT GetBoundingBox() { return m_pPlayerImage->GetBoundingBox(); }
	float GetPosX() { return m_pPlayerImage->GetPosX(); }
	float GetPosY() { return m_pPlayerImage->GetPosY(); }
	float GetMoveSpeed() { return m_fMoveSpeed; }
	bool GetMapMove() { return m_isMapMove; }
	float GetSizeX() { return m_pPlayerImage->GetFrameWidth(); }
	float GetSizeY() { return m_pPlayerImage->GetFrameHeight(); }
#pragma endregion
};

