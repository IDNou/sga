#pragma once
#include "cGameNode.h"

class cDungeon3 : public cGameNode
{
private:
	
public:
	cDungeon3() {};
	virtual ~cDungeon3() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

