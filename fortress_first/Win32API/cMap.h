#pragma once

class cMap
{
private:
	cImage*		m_pImgBackgoround;
	int			m_nSourX;
	int			m_nMoveSpeed;
	int			m_SlowSpeedDealy;

	int			moveBackgrounX;

	cImage*		m_pImgGround;
	cImage*		m_pImgDraw;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

#pragma region Get
	int GetSlowSpeed() { return m_SlowSpeedDealy; }
	int GetMoveX() { return moveBackgrounX; }
#pragma endregion

#pragma region Set
	void SetSlowSpeed(int delay) { m_SlowSpeedDealy = delay; }
	void SetMoveX(int moveX) { moveBackgrounX = moveX; }
#pragma endregion
};

