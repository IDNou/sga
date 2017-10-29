#pragma once
#include "cImage.h"

class cPlayer;
class cMap;
class cProgressBar;


class cObjects
{
private:
	
	
	cPlayer*	m_pPlayer;		// �÷��̾� ���� ������
	cMap*		m_pMap;			// �� ���� ������
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

