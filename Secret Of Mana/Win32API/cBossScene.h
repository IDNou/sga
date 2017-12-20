#pragma once
#include "cGameNode.h"

class cPlayer;
class cMonster;

class cBossScene : public cGameNode
{
private:
	cImage* BackGround;
	cImage* BackGround_Magenta;
	cImage*	EmptyBuffer;
	cPlayer* Player;
	cMonster* Boss;

	RECT ViewPort;

public:
	cBossScene() {};
	virtual ~cBossScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

