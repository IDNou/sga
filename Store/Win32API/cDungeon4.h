#pragma once
#include "cGameNode.h"

struct enermy2
{
	int PosX;
	int PosY;
	int Money;
	int ATK;
	bool isDie;
};
class cDungeon4 : public cGameNode
{
private:
	enermy2 Test;
	vector<enermy2>  vecTest;

	PlayerStat savePlayer;

public:
	cDungeon4() {};
	virtual ~cDungeon4() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};
