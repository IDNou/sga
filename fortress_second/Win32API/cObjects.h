#pragma once
#include "cImage.h"

class cPlayer;
class cMap;
class cProgressBar;

enum Left_Right
{
	LEFT = 0,
	RIGHT
};

struct tagMushRoom
{
	int			PosX;
	int			PosY;
	Left_Right	dir;
	bool		isDie;
};


class cObjects
{
private:
	
	
	cPlayer*	m_pPlayer;		// 플레이어 참조 포인터
	cMap*		m_pMap;			// 맵 참조 데이터
	cProgressBar* m_pBossHpBar;

	cImage*		m_pMushRoom;
	cImage*		m_pMapImg;
	tagMushRoom		sct_MushRooom;
	vector<tagMushRoom> vecMushRoom;

	int			moveGroundX;
	int			framecount;

	int			BprobeX;
	int			BprobeY;
	int			LprobeX;
	int			LprobeY;
	int			RprobeX;
	int			RprobeY;
	

public:
	cObjects();
	~cObjects();

	void Setup();
	void Update();
	void Render();

#pragma region Get
	
#pragma endregion

#pragma region Set
	void SetPlayer(cPlayer* player) { m_pPlayer = player; }
	void SetMap(cMap* map) { m_pMap = map; }
	void SetMoveGroundX(int moveX) { moveGroundX = moveX; }
#pragma endregion
};

