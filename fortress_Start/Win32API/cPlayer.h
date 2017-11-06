#pragma once

class cProgressBar;
class cMap;

#define MAP1_Y (WINSIZEY - 110)

enum PlayerNum
{
	FirstPlayer = 0,
	SecondPlayer
};

enum PlayerDir
{
	LEFT =0,
	RIGHT
};

struct tagPlayer
{
	PlayerNum		Number;
	PlayerDir		Dir;
	cImage*			t_pPlayerImage;
	cProgressBar*	m_pHpBar;
	float			m_fMaxHp;
	float			m_fCurrHp;
	float			m_fGravity;
	bool			isDie;
};

class cPlayer
{
private:
	//cImage*			m_pPlayerImage;		// 플레이어 이미지 파일
	//cImage*			m_pPlayerSecondImage;
	cImage*			m_pBomb;

	float			m_fGravity;			// 중력 (점프시 사용)
	float			m_fMoveSpeed;		// 캐릭터 이동 스피드
	
	//폭탄요소들
	float			bombPosX;
	float			bombPosY;
	float			bombAngle;
	float			bombPower;
	bool			isBombActivity;
	int				bombCount;

	
	tagPlayer		Player;
	vector<tagPlayer> vecPlayer;
	PlayerNum		checkTurn;

	cMap*			m_pMap;
	cImage*			m_pImgMapBuffer;	// 배경 정보 이미지(마젠타가 들어 있는 픽셀 충돌용 맵)

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();

	void WhoUpdate(tagPlayer &t_pPlayer);
	void WhoRender(tagPlayer &t_pPlayer);

#pragma region Set
	void SetMap(cMap* map) { m_pMap = map; }
#pragma endregion

#pragma region Get
//	RECT GetBoundingBox() { return m_pPlayerImage->GetBoundingBox(); }
	vector<tagPlayer> &GetVecPlayer() { return vecPlayer; }
	PlayerNum GetPlayerTurn() { return checkTurn; }
//	float GetPosX() { return m_pPlayerImage->GetPosX(); }
//	float GetPosY() { return m_pPlayerImage->GetPosY(); }
	float GetMoveSpeed() { return m_fMoveSpeed; }
//	float GetSizeX() { return m_pPlayerImage->GetFrameWidth(); }
//	float GetSizeY() { return m_pPlayerImage->GetFrameHeight(); }
#pragma endregion
};

