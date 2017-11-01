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
#pragma endregion
};

