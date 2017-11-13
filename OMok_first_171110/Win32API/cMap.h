#pragma once

class cPlayer;

class cMap
{
private:

	cPlayer*	m_pPlayer;

	cImage* alphaStone;

	float			time;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	float GetTime() { return time; }

	void SetPlayer(cPlayer* player) { m_pPlayer = player; }
	void SetTime(float getTime) { time = getTime; }

};