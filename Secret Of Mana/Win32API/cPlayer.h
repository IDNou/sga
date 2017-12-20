#pragma once
#include "cItem.h"

#define MOVECOUNT 5
#define MoveSpeed 2
#define PlayerSize 30

enum PlayerDir
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN,
	DIREND
};

class cPlayer
{
private:
	cImage* PlayerImage;
	cImage* Terrain;
	vector<cItem*> PlayerInven;

	RECT	ViewPort;
	RECT	AttackRect;

	int LV;
	int HP;
	int MAXHP;
	int ATK;
	int DEF;
	int EXP;
	int MAXEXP;
	int MONEY;

	int MoveCount;
	int BuyCount;
	int PosX;
	int PosY;
	int TerrainWidth;
	int TerrainHeight;
	int LProveX;
	int LProveY;
	int RProveX;
	int RProveY;
	int TProveX;
	int TProveY;
	int BProveX;
	int BProveY;
	

	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	bool isAttack;
	bool isBuy;

	PlayerDir Direction;

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render(HDC hdc);

#pragma region Get
	cImage* GetPlayerImage() { return PlayerImage; }
	RECT GetViewPort() { return ViewPort; }
	int	GetPosX() { return PosX; }
	int GetPosY() { return PosY; }
	RECT GetAttackRange() { return AttackRect; }
	int GetHP() { return HP; }
	int GetMAXHP() { return MAXHP; }
	int GetEXP() { return EXP; }
	int GetDEF() { return DEF; }
	int GetATK() { return ATK; }
	int GetLV() { return LV; }
	int GetMoney() { return MONEY; }
	bool GetIsAttack() { return isAttack; }
	bool GetIsBuy() { return isBuy; }
	PlayerDir GetPlayerDir() { return Direction; }
	vector<cItem*> &GetPlayerInven() { return PlayerInven; }
#pragma endregion
#pragma regiom Set
	void SetPlayerImage(cImage* Image) { PlayerImage = Image; }
	void SetTerrainWidth(int Width) { TerrainWidth = Width; }
	void SetTerrainHeight(int Height) { TerrainHeight = Height; }
	void SetTerrain(cImage* img) { Terrain = img; }
	void SetViewPort(RECT rt) { ViewPort = rt; }
	void SetPosX(int X) { PosX = X;}
	void SetPosY(int Y) { PosY = Y;}
	void SetLV(int pl_lv) { LV = pl_lv; }
	void SetHp(int pl_hp) { HP = pl_hp; }
	void SetMAXHP(int pl_maxhp) { MAXHP = pl_maxhp; }
	void SetATK(int pl_atk) { ATK = pl_atk; }
	void SetDEF(int pl_def) { DEF = pl_def; }
	void SetEXP(int pl_exp) { EXP = pl_exp; }
	void SetMAXEXP(int pl_maxexp) { MAXEXP = pl_maxexp; }
	void SetMONEY(int pl_money) { MONEY = pl_money; }
	void SetPlayerInven(vector<cItem*> inven) { PlayerInven = inven; }
	void SetIsBuy(bool buy) { isBuy = buy; }
#pragma endregion
};

