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

class cObjects
{
private:
	
	
	cPlayer*	m_pPlayer;		// �÷��̾� ���� ������
	cMap*		m_pMap;			// �� ���� ������
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
	cObjects();
	~cObjects();

	void Setup();
	void Update();
	void Render();

#pragma region Get
	vector<tagMushRoom> &GetMushRoom() { return vecMushRoom; }
	vector<tagMushRoomItem> &GetMushRoomItem() { return vecMushRoomItem; }
	cImage*	&GetMoveBar() { return m_pMoveBar; }
#pragma endregion

#pragma region Set
	void SetPlayer(cPlayer* player) { m_pPlayer = player; }
	void SetMap(cMap* map) { m_pMap = map; }
	void SetMoveGroundX(int moveX) { moveGroundX = moveX; }
#pragma endregion
};

