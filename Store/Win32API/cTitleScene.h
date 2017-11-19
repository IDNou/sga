#pragma once
#include "cGameNode.h"

struct PlayerStat
{
	cImage* playerImage;
	int		HP;
	int		ATK;
	int		DEF;
	int		Kit;
	int		MaNaKit;
	int		Money;
};

class cTitleScene :	public cGameNode
{
private:
	cImage* store1;
	cImage*	store2;
	cImage*	dungeon1;
	cImage*	dungeon2;
	cImage*	stat;
	
	PlayerStat player;

public:
	cTitleScene() {};
	virtual ~cTitleScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

