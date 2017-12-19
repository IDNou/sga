#include "stdafx.h"
#include "cPlayerManager.h"


cPlayerManager::cPlayerManager()
{
}


cPlayerManager::~cPlayerManager()
{
}

void cPlayerManager::Start()
{
	json LoadPlayer;
	ifstream jsoninfo;
	jsoninfo.open("PlayerInfo.json");
	jsoninfo >> LoadPlayer;
	jsoninfo.close();

	Player = new cPlayer;
	Player->SetHp(LoadPlayer["Player"]["HP"]);
	Player->SetLV(LoadPlayer["Player"]["LV"]);
	Player->SetMAXHP(LoadPlayer["Player"]["MAXHP"]);
	Player->SetATK(LoadPlayer["Player"]["ATK"]);
	Player->SetDEF(LoadPlayer["Player"]["DEF"]);
	Player->SetEXP(LoadPlayer["Player"]["EXP"]);
	Player->SetMONEY(LoadPlayer["Player"]["MONEY"]);
	Player->SetMAXEXP(LoadPlayer["Player"]["MAXEXP"]);

}

void cPlayerManager::Update()
{
}

void cPlayerManager::Render()
{
}
