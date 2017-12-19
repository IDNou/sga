#pragma once
#include "cGameNode.h"

#define Infinite 999999

struct tagNode
{
	POINT	m_ptMousePosition;
	int		m_intNodeNum;
	int		via;
	int		cost;
	bool	open;
	vector<int> m_vNodeNumber;
};

struct tagLinePos
{
	float PreveX;
	float PreveY;
	float NextX;
	float NextY;
	float edgeCost;
	int	PreveIndex;
	int NextIndex;
};
class cTitleScene :	public cGameNode
{
private:
	float PosX;
	float PosY;

	tagLinePos LinePos;
	tagNode	Node;
	vector<int> chart;

	int saveNode;
	int connectNode;
	int currentNode;
	int NextNode;
	int	arriveNode;
	int arriveNode2;

	bool isEdge;
	bool isStart;
	bool isChainge;
	bool isCalculate;
	bool isDone;
	bool isCalculateDone;

	float time;
	int	count;
	int chartSize;
	vector<tagNode> m_vPointPath;
	vector<tagLinePos> m_vLinePos;

public:
	cTitleScene() {};
	virtual ~cTitleScene() {};

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	bool CalculateDone();
};

