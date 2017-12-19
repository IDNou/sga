#pragma once
#include "cGameNode.h"
class cTitleScene :	public cGameNode
{
private:
	cImage* bg;
	int alhpa;
	bool isSwitch;
public:
	cTitleScene() {};
	virtual ~cTitleScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

