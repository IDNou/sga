#pragma once
#include "cPlayer.h"

class cPlayer;

enum MoveDir {
	MON_LEFT = 0,
	MON_RIGHT,
	MON_UP,
	MON_DOWN,
	MON_END
};

enum MonsterType
{
	MONTYPE_SHORT = 0,
	MONTYPE_LONG,
	MONTYPE_END
};

class cMonster
{
private:
	cPlayer* Player;
	cImage* MonsterImage;
	cImage* Terrain;
	RECT SeachRect;
	RECT AttackRect;

	float PosX;
	float PosY;
	int Monster_FrameX;
	int Monster_FrameY;

	string Name;
	MonsterType Type;
	int HP;
	int ATK;
	int DEF;
	int EXP;
	int MONEY;
	int Area;
	bool isDie;
	bool isHit;
	bool isDivain;

	POINT LProve;
	POINT RProve;
	POINT TProve;
	POINT BProve;

	//===========
	int DirDelay;
	int MoveDelay;
	int DivainCount;
	int	AlphaValue;
	int PushDir;
	int AttackCount;
	int AttackDelay;
	float Angle;

	MoveDir Direction;
	bool isMoveStart;
	bool isAttackMode;
	bool isSeachMode;
	bool isAttacking;
	bool isShowAttackRect;
	bool AlphaPlag;

public:
	cMonster();
	~cMonster();

	void Setup();
	void Update();
	void Render(HDC hdc);

#pragma region Get
	cImage* &GetMonsterImage() { return MonsterImage; }
	float GetPosX() { return PosX; }
	float GetPosY() { return PosY; }
	POINT GetLProve() { return LProve; }
	POINT GetRProve() { return RProve; }
	POINT GetTProve() { return TProve; }
	POINT GetBProve() { return BProve; }
	string GetName() { return Name; }
	MonsterType GetType() { return Type; }
	RECT GetSeachRect() { return SeachRect; }
	MoveDir GetDir() { return Direction; }
	int GetHP() { return HP; }
	int GetEXP() { return EXP; }
	int GetDEF() { return DEF; }
	int GetATK() { return ATK; }
	int GetMONEY() { return MONEY; }
	int GetFrameX() { return Monster_FrameX; }
	int GetFrameY() { return Monster_FrameY; }
	int GetArea() { return Area; }
	bool GetIsDie() { return isDie; }
	bool GetIsHit() { return isHit; }
	bool GetIsDivain() { return isDivain; }
	bool GetIsAttackMode() { return isAttackMode; }
	bool GetIsSeachMode() { return isSeachMode; }
	bool GetIsAttacking() { return isAttacking; }
	bool GetIsShowAttackRect() { return isShowAttackRect; }
#pragma endregion

#pragma region Set
	void SetPosX(float x) { PosX = x; }
	void SetPosY(float y) { PosY = y; }
	void SetLProve(POINT mon_LP) { LProve = mon_LP; }
	void SetRProve(POINT mon_RP) { RProve = mon_RP; }
	void SetTProve(POINT mon_TP) { TProve = mon_TP; }
	void SetBProve(POINT mon_BP) { BProve = mon_BP; }
	void SetFrameX(int x) { Monster_FrameX = x; }
	void SetFrameY(int y) { Monster_FrameY = y; }
	void SetMonsterImage(cImage* Image) { MonsterImage = Image; }
	void SetName(string mon_name) { Name = mon_name; }
	void SetTerrain(cImage* terrain) { Terrain = terrain; }
	void SetType(MonsterType mon_type) { Type = mon_type; }
	void SetDir(MoveDir dir) { Direction = dir; }
	void SetHP(int mon_hp) { HP = mon_hp; }
	void SetATK(int mon_atk) { ATK = mon_atk; }
	void SetDEF(int mon_def) { DEF = mon_def; }
	void SetEXP(int mon_exp) { EXP = mon_exp; }
	void SetMoney(int mon_money) { MONEY = mon_money; }
	void SetIsDie(bool mon_die) { isDie = mon_die; }
	void SetIsHit(bool mon_hit) { isHit = mon_hit; }
	void SetIsDivain(bool mon_divain) { isDivain = mon_divain; }
	void SetPushDir(int dir) { PushDir = dir; }
	void SetArea(int mon_area) { Area = mon_area; }
	void SetSeachRect(RECT mon_seachrect) { SeachRect = mon_seachrect; }
	void SetIsAttackMode(bool mon_attackmode) { isAttackMode = mon_attackmode; }
	void SetIsAttacking(bool mon_attacking) { isAttacking = mon_attacking; }
	void SetIsSeachMode(bool mon_seachmode) { isSeachMode = mon_seachmode; }
	void SetIsShowAttackRect(bool mon_showattackrect) { isShowAttackRect = mon_showattackrect; }
#pragma endregion
};

