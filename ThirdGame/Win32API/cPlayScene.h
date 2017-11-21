#pragma once
#include "cGameNode.h"

class cPlayScene : public cGameNode
{
private:
	enum DIRECTION { LEFT, RIGHT, UP, DOWN, WAIT };

private:
	cImage*		m_pImgNumbers;
	int			m_nValue[4][4];

private:
	void Move(bool& move, DIRECTION dir);
	void MoveBlock(bool& move, int& dest, int& origin);
	void NewNumber(const bool move);
	void Merge(bool& move, DIRECTION dir);
	void MergeBlock(bool& move, int& dest, int& origin);

public:
	cPlayScene() {};
	virtual ~cPlayScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

