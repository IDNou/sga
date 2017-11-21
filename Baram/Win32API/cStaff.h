#pragma once
#include "cGameNode.h"
class cStaff : public cGameNode
{
public:
	cStaff() {};
	virtual ~cStaff() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

