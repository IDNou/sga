#include "stdafx.h"
#include "cMonsterManager.h"


cMonsterManager::cMonsterManager()
{
}


cMonsterManager::~cMonsterManager()
{
}

void cMonsterManager::Start()
{
	MonsterList;
	ifstream json_List;
	json_List.open("MonsterList.json");
	json_List >> MonsterList;
	json_List.close();
}

void cMonsterManager::Update()
{
}

void cMonsterManager::Render()
{
}

cMonster * cMonsterManager::GetRabit()
{
	Monster = new cMonster;
	//Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
	Monster->Setup();
	Monster->SetType(MonsterList["Rabit"]["TYPE"]);
	Monster->SetHP(MonsterList["Rabit"]["HP"]);
	Monster->SetATK(MonsterList["Rabit"]["ATK"]);
	Monster->SetDEF(MonsterList["Rabit"]["DEF"]);
	Monster->SetEXP(MonsterList["Rabit"]["EXP"]);
	Monster->SetMoney(GetRandom(MonsterList["Rabit"]["MINMONEY"], MonsterList["Rabit"]["MAXMONEY"]));

	return Monster;
}

cMonster * cMonsterManager::GetBee()
{
	Monster = new cMonster;
	//Monster->SetMonsterImage(g_pImageManager->FindImage("Bee"));
	Monster->Setup();
	Monster->SetType(MonsterList["Bee"]["TYPE"]);
	Monster->SetHP(MonsterList["Bee"]["HP"]);
	Monster->SetATK(MonsterList["Bee"]["ATK"]);
	Monster->SetDEF(MonsterList["Bee"]["DEF"]);
	Monster->SetEXP(MonsterList["Bee"]["EXP"]);
	Monster->SetMoney(GetRandom(MonsterList["Rabit"]["MINMONEY"], MonsterList["Rabit"]["MAXMONEY"]));

	return Monster;
}

cMonster * cMonsterManager::GetCobolt()
{
	Monster = new cMonster;
	//Monster->SetMonsterImage(g_pImageManager->FindImage("Cobolt"));
	Monster->Setup();
	Monster->SetType(MonsterList["Cobolt"]["TYPE"]);
	Monster->SetHP(MonsterList["Cobolt"]["HP"]);
	Monster->SetATK(MonsterList["Cobolt"]["ATK"]);
	Monster->SetDEF(MonsterList["Cobolt"]["DEF"]);
	Monster->SetEXP(MonsterList["Cobolt"]["EXP"]);
	Monster->SetMoney(GetRandom(MonsterList["Rabit"]["MINMONEY"], MonsterList["Rabit"]["MAXMONEY"]));

	return Monster;
}
