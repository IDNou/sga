#pragma once

class cPlayer;
class cObjects;

class cMap
{
private:
	cImage*		m_pImgBackgoround;
	cImage*		m_pImgGround;
	cImage*		m_pImgDraw;
	cImage*		m_pImgMagenta;

	cPlayer*     m_pPlayer;
	cObjects*	 m_pObject;

	int PosX;
	int PosY;
	int	MapPosX;
	int	MapPosY;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();
	
#pragma region Get

#pragma endregion

#pragma region Set
	void SetPlayer(cPlayer* player) { m_pPlayer = player; }
	void SetObject(cObjects* object) { m_pObject = object; }
	void SetPosXY(int x, int y) {
		PosX = x; PosY = y;
		if (x > WINSIZEX / 2)
			MapPosX = x - WINSIZEX / 2;
		else
			MapPosX = 0;
		if (y > WINSIZEY / 2)
			MapPosY = y - WINSIZEY / 2;
		else
			MapPosY = 0;
	}
#pragma endregion
};

