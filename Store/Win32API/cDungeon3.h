#pragma once
#include "cGameNode.h"

struct enermy
{
	int PosX;
	int PosY;
	int Money;
	int ATK;
	bool isDie;
};

class cDungeon3 : public cGameNode
{
private:
	enermy Test;
	vector<enermy>  vecTest;

	PlayerStat savePlayer;

public:
	cDungeon3() {};
	virtual ~cDungeon3() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

