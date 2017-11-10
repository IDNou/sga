#pragma once

class cMap;

struct tagStone
{
	cImage* stoneImage;
	float	PosX;
	float	PosY;
	int		stoneColor;
	int		stoneUID;
	bool	isActivity;
};

class cPlayer
{
private:

	cMap*			m_pMap;
	tagStone		Stone;
	vector<tagStone> vecStone;
	int				alretColor;

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();

	vector<tagStone> &GetVecStone() { return vecStone; }

	void SetMap(cMap* map) { m_pMap = map; }

};

