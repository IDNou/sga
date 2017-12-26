#pragma once
#include "cGameNode.h"

class cPlayer;
class cBoss;

class cBossScene : public cGameNode
{
private:
	cImage* BackGround;
	cImage* BackGround_Magenta;
	cImage*	EmptyBuffer;
	cPlayer* Player;
	cBoss* Boss;

	json Place;

	int SeachTime;

	RECT ViewPort;

public:
	cBossScene() {};
	virtual ~cBossScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

