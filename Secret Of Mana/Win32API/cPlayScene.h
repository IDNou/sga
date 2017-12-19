#pragma once
#include "cGameNode.h"

class cPlayer;
class cMonster;

class cPlayScene : public cGameNode
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
	cPlayScene() {};
	virtual ~cPlayScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

