#pragma once
#include "cGameNode.h"

class cDungeon4 : public cGameNode
{
private:

public:
	cDungeon4() {};
	virtual ~cDungeon4() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};
