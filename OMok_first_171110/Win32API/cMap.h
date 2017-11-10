#pragma once

class cPlayer;

class cMap
{
private:

	cPlayer*	m_pPlayer;

	cImage* alphaStone;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	void SetPlayer(cPlayer* player) { m_pPlayer = player; }

};