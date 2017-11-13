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
	int				saveUID;
	int				rowCount;
	int				colCount;
	int				LdiagoCount;
	int				RdiagoCount;
	int				victoryCount;

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();

	vector<tagStone> &GetVecStone() { return vecStone; }
	int	GetAlretColor() { return alretColor; }

	void SetMap(cMap* map) { m_pMap = map; }
	void SetAlretColor(int Color) { alretColor = Color; }

};

