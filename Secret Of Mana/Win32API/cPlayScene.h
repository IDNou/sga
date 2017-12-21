#pragma once
#include "cGameNode.h"

class cPlayer;
class cMonster;

enum tagVillageArea
{
	Village_One = 1,
	Village_Two,
	Village_Three,
	Village_Four
};

class cPlayScene : public cGameNode
{
private:
	cImage* BackGround;
	cImage* BackGround_Magenta;
	cImage*	EmptyBuffer;
	cPlayer* Player;
	cMonster* Monster;
	tagVillageArea Area;
	map<tagVillageArea,cMonster*> map_Monster;
	map<tagVillageArea, cMonster*>::iterator map_IterMonster;
	vector<cMonster*> m_vMonster;

	int CreateTime;
	bool CreateAria[4];

	RECT ViewPort;

public:
	cPlayScene() {};
	virtual ~cPlayScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

