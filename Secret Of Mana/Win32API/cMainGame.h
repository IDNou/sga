#pragma once
#include "cGameNode.h"

class cSetupInfo;

class cMainGame : public cGameNode
{
private:
	cSetupInfo * SetupInfo;
	json ItemList;
	bool isPause;

public:
	cMainGame();
	virtual ~cMainGame();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};