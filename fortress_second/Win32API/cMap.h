#pragma once

enum BoxType
{
	eWall = 0,
	eBox,
	eMushRoomBox
};

struct tagWall
{
	int		PosX;
	int		PosY;
	int		MushRoomItemNum;
	BoxType type;
	bool	isBreak;
};

class cMap
{
private:
	cImage*		m_pImgBackgoround;
	int			m_nSourX;
	int			m_nMoveSpeed;
	int			m_SlowSpeedDealy;

	int			moveBackgrounX;
	tagWall		wall;

	cImage*		m_pImgGround;
	cImage*		m_pImgDraw;
	cImage*		m_pImgMagenta;

	vector<tagWall> vecWall;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

#pragma region Get
	int GetSlowSpeed() { return m_SlowSpeedDealy; }
	int GetMoveX() { return moveBackgrounX; }
	vector<tagWall> &GetVecWall() { return vecWall; }
#pragma endregion

#pragma region Set
	void SetSlowSpeed(int delay) { m_SlowSpeedDealy = delay; }
	void SetMoveX(int moveX) { moveBackgrounX = moveX; }
#pragma endregion
};

