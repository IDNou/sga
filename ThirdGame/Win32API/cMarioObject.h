#pragma once

class cMarioPlayer;
class cMarioMap;
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

struct tagMushRoomItem
{
	int PosX;
	int PosY;
	int	objMushRoomItemNum;
	bool isActiveMushRoomItem;
	bool isDie;
	Left_Right	dir;
};

struct tagFlower
{
	int PosX;
	int PosY;
	bool isDie;
};

class cMarioObject
{
private:


	cMarioPlayer*	m_pPlayer;		// 플레이어 참조 포인터
	cMarioMap*		m_pMap;			// 맵 참조 데이터
	cProgressBar* m_pBossHpBar;

	cImage*		m_pMushRoom;
	cImage*		m_pMapImg;
	cImage*		m_pItemMushRoom;
	cImage*		m_pMoveBar;
	cImage*		m_pFlower;
	tagMushRoom		sct_MushRooom;
	tagMushRoomItem		sct_MushRoomItem;
	vector<tagMushRoom> vecMushRoom;
	vector<tagMushRoomItem> vecMushRoomItem;

	int			moveGroundX;
	int			framecount;

	int			BprobeX;
	int			BprobeY;
	int			LprobeX;
	int			LprobeY;
	int			RprobeX;
	int			RprobeY;

public:
	cMarioObject();
	~cMarioObject();

	void Setup();
	void Update();
	void Render();

#pragma region Get
	vector<tagMushRoom> &GetMushRoom() { return vecMushRoom; }
	vector<tagMushRoomItem> &GetMushRoomItem() { return vecMushRoomItem; }
	cImage*	&GetMoveBar() { return m_pMoveBar; }
#pragma endregion

#pragma region Set
	void SetPlayer(cMarioPlayer* player) { m_pPlayer = player; }
	void SetMap(cMarioMap* map) { m_pMap = map; }
	void SetMoveGroundX(int moveX) { moveGroundX = moveX; }
#pragma endregion
};

