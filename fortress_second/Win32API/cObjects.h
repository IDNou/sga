#pragma once
#include "cImage.h"

class cPlayer;
class cMap;
class cProgressBar;


class cObjects
{
private:
	
	
	cPlayer*	m_pPlayer;		// 플레이어 참조 포인터
	cMap*		m_pMap;			// 맵 참조 데이터
	cProgressBar* m_pBossHpBar;

	

public:
	cObjects();
	~cObjects();

	void Setup();
	void Update();
	void Render();

#pragma region Get
	
#pragma endregion

#pragma region Set
	void SetPlayer(cPlayer* player) { m_pPlayer = player; }
	void SetMap(cMap* map) { m_pMap = map; }
#pragma endregion
};

