#pragma once
#include "cGameNode.h"
class cLoad :
	public cGameNode
{
public:
	cLoad() {};
	virtual ~cLoad() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

