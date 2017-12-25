#pragma once
#include "cItem.h"
#include "cMonster.h"
#include "cBoss.h"
#include "cProgressBar.h"

#define MOVECOUNT 5
#define MoveSpeed 2
#define PlayerSize 30

class cMonster;
class cBoss;
class cProgressBar;

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
	cMonster* Monster;
	cBoss* Boss;
	cImage* PlayerImage;
	cImage* Terrain;
	cImage* CommunicationBox;
	vector<cItem*> PlayerInven;
	json	LevelInfo;
	cProgressBar* HPBar;

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
	int ItemATK;
	int ItemDEF;

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
	int DivainCount;
	int AlphaValue;
	int DamageBuffer;
	

	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	bool isAttack;
	bool isBuy;
	bool isLevelUp;
	bool isHit;
	bool isDivain;
	bool isPush;
	bool AlphaPlag;

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
	int GetMAXEXP() { return MAXEXP; }
	int GetDEF() { return DEF; }
	int GetATK() { return ATK; }
	int GetLV() { return LV; }
	int GetMoney() { return MONEY; }
	int GetItemATK() { return ItemATK; }
	int GetItemDEF() { return ItemDEF; }
	bool GetIsAttack() { return isAttack; }
	bool GetIsBuy() { return isBuy; }
	PlayerDir GetPlayerDir() { return Direction; }
	vector<cItem*> &GetPlayerInven() { return PlayerInven; }
	bool GetIsHit() { return isHit; }
	bool GetIsDivain() { return isDivain; }
	bool GetIsPush() { return isPush; }
	cMonster* GetMonnster() { return Monster; }
	int GetDamageBuffer() { return DamageBuffer; }
#pragma endregion
#pragma regiom Set
	void SetPlayerImage(cImage* Image) { PlayerImage = Image; }
	void SetTerrainWidth(int Width) { TerrainWidth = Width; }
	void SetTerrainHeight(int Height) { TerrainHeight = Height; }
	void SetTerrain(cImage* img) { Terrain = img; }
	void SetViewPort(RECT rt) { ViewPort = rt; }
	void SetPlayerDir(PlayerDir dir) { Direction = dir; }
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
	void SetItemATK(int pl_itematk) { ItemATK = pl_itematk; }
	void SetItemDEF(int pl_itemdef) { ItemDEF = pl_itemdef; }
	void SetPlayerInven(vector<cItem*> inven) { PlayerInven = inven; }
	void SetIsBuy(bool buy) { isBuy = buy; }
	void SetIsHit(bool pl_ishit) { isHit = pl_ishit; }
	void SetisDivain(bool pl_isdivain) { isDivain = pl_isdivain; }
	void SetMonster(cMonster* pl_monster) { Monster = pl_monster; }
	void SetBoss(cBoss* pl_Boss) { Boss = pl_Boss; }
	void SetIsPush(bool pl_push) { isPush = pl_push; }
	void SetDamageBuffer(int pl_damagebuffer) { DamageBuffer = pl_damagebuffer; }
#pragma endregion
};

