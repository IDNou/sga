#pragma once

#define MoveCount 7
#define MoveSpeed 10

class cItemKind;

enum PlayerJob
{
	worrior = 1,
	mage
};

class cTestPlayer
{
private:
	float	PosX;
	float	PosY;

	PlayerJob	Job;
	cImage*		PlayerImage;

	// 스탯
	int		HP;
	int		MP;
	int		ATK;
	int		DEF;
	int		STR;
	int		INT;
	int		AGL;

	// 유동적인것
	int		Money;


	bool	isDie;
	
	//이외의 것들
	int		count;
	int		Incount;
	bool	Lock;

	cItemKind*	kind;
	
public:
	cTestPlayer();
	~cTestPlayer();

	void Setup();
	void Update();
	void Render();

#pragma region Get

#pragma endregion

#pragma region Set
#pragma endregion
};

