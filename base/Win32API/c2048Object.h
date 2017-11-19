#pragma once

class c2048Map;
class c2048Player;

#define Width 125
#define Height 108

struct tagBlock
{
	cImage* m_pImageBlock;
	float PosX;
	float PosY;
	int	Number;
	int	uId;
	bool isExist;
};

class c2048Object
{
private:
	c2048Map*		m_pMap;
	c2048Player*	m_pPlayer;

	tagBlock	block;
	vector<tagBlock> vecBlock;
	vector<tagBlock> vecEqual;

	int			BlockWidth;
	int			BlockHeight;
	int			count;
	int			FullCount;

	bool		isVictory;

public:
	c2048Object();
	~c2048Object();

	void Setup();
	void Update();
	void Render();

	vector<tagBlock> &GetVecBlock() { return vecBlock; }
	vector<tagBlock> &GetVecEqual() { return vecEqual; }
	int	GetBlockWidth() { return BlockWidth; }
	int	GetBlockHeight() { return BlockHeight; }
	bool GetIsVictory() { return isVictory; }

	void SetPlayer(c2048Player* player) { m_pPlayer = player; }
	void SetMap(c2048Map* map) { m_pMap = map; }
	void SetVecEqual(vector<tagBlock> equal) { vecEqual = equal; }
};

