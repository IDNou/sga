#pragma once

#include "cGameNode.h"

class cEndingScene : public cGameNode
{
private:

public:
	cEndingScene() {};
	virtual ~cEndingScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

