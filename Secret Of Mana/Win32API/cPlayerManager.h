#pragma once
#include "cSingletonBase.h"
#include "cPlayer.h"

#define g_pPlayerManager cPlayerManager::GetInstance()

class cPlayer;

class cPlayerManager : public cSingletonBase<cPlayerManager>
{
private:
	cPlayer* Player;

public:
	cPlayerManager();
	~cPlayerManager();

	void Start();
	void Update();
	void Render();

	cPlayer* GetPlayer() { return Player; }
};

