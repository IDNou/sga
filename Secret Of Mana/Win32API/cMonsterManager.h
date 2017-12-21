#pragma once
#include "cSingletonBase.h"
#include "cMonster.h"

#define g_pMonsterManager cMonsterManager::GetInstance()

class cMonster;

class cMonsterManager : public cSingletonBase<cMonsterManager>
{
private:
	cMonster*	Monster;
	//map<string, cMonster*> map_Mon;
	json MonsterList;

public:
	cMonsterManager();
	~cMonsterManager();

	void Start();
	void Update();
	void Render();

	cMonster* GetRabit();
	cMonster* GetBee();
	cMonster* GetCobolt();
};

