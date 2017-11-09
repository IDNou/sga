#pragma once

class cMap;
class cPlayer;

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

class cObject
{
private:
	cMap*		m_pMap;
	cPlayer*	m_pPlayer;

	tagBlock	block;
	vector<tagBlock> vecBlock;

	int			BlockWidth;
	int			BlockHeight;
	int			count;
	int			FullCount;

public:
	cObject();
	~cObject();

	void Setup();
	void Update();
	void Render();

	vector<tagBlock> &GetVecBlock() { return vecBlock; }
	int	GetBlockWidth() { return BlockWidth; }
	int	GetBlockHeight() { return BlockHeight; }

	void SetPlayer(cPlayer* player) { m_pPlayer = player; }
	void SetMap(cMap* map) { m_pMap = map; }
};

