#pragma once

#include "cGameNode.h"

class cPlayer;

#define MessageWidth 30
#define MessegeHeight 40

class cSetupInfo : public cGameNode
{
private:
	cPlayer* Player;
	cImage* BackGround;
	cImage* StatMessegeBox;
	int boxSize;
	int count;
	int InvenWidth;
	int InvenHeight;
	vector<cImage*> vecImage;
public:
	cSetupInfo() {};
	virtual ~cSetupInfo() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

