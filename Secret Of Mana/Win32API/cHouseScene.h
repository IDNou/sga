#pragma once
#include "cGameNode.h"

class cPlayer;
class cStore;

class cHouseScene : public cGameNode
{
private:
	cPlayer* Player;
	cStore* Store;
	cImage* BackGround;
	cImage* BackGround_Magenta;
	cImage* EmptyBuffer;
	RECT ViewPort;
	 
	//ªÛ¡°
	bool isBuy;

public:
	cHouseScene() {};
	virtual ~cHouseScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

