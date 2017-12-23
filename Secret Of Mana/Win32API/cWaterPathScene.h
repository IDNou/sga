#pragma once
#include "cGameNode.h"

class cMonster;
class cPlayer;

enum tagWaterArea
{
	Water_One = 1,
	Water_Two,
	Water_Three,
	Water_Four,
	Water_Five,
	Water_SiX,
	Water_Seven,
	Water_eight
};


class cWaterPathScene : public cGameNode
{
private:
	cImage* BackGround;
	cImage* BackGround_Magenta;
	cImage*	EmptyBuffer;
	cPlayer* Player;
	cMonster* Monster;
	tagWaterArea Area;
	map<tagWaterArea, cMonster*> map_Monster;
	vector<cMonster*> m_vMonster;

	int CreateTime;
	int SeachTime;
	bool CreateAria[4];

	RECT ViewPort;

public:
	cWaterPathScene() {};
	virtual ~cWaterPathScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

