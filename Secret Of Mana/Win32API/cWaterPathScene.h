#pragma once
#include "cGameNode.h"

class cMonster;
class cPlayer;

class cWaterPathScene : public cGameNode
{
private:
	cImage* BackGround;
	cImage* BackGround_Magenta;
	cImage*	EmptyBuffer;
	cPlayer* Player;
	cMonster* Monster;
	vector<cMonster*> m_vMonster;

	RECT ViewPort;

public:
	cWaterPathScene() {};
	virtual ~cWaterPathScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

