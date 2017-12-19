#pragma once

enum MoveDir {
	MON_LEFT = 0,
	MON_RIGHT,
	MON_UP,
	MON_DOWN,
	MON_END
};

class cMonster
{
private:
	cImage* MonsterImage;
	cImage* Terrain;

	int PosX;
	int PosY;

	int HP;
	int ATK;
	int DEF;
	int EXP;
	int MONEY;
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
	MoveDir Direction;
	bool isMoveStart;
	bool AlpghPlag;

public:
	cMonster();
	~cMonster();

	void Setup();
	void Update();
	void Render(HDC hdc);

#pragma region Get
	cImage* &GetMonster() { return MonsterImage; }
	int GetPosX() { return PosX; }
	int GetPosY() { return PosY; }
	int GetHP() { return HP; }
	int GetEXP() { return EXP; }
	int GetDEF() { return DEF; }
	int GetATK() { return ATK; }
	int GetMONEY() { return MONEY; }
	bool GetIsDie() { return isDie; }
	bool GetIsHit() { return isHit; }
	bool GetIsDivain() { return isDivain; }
#pragma endregion

#pragma region Set
	void SetPosX(int x) { PosX = x; }
	void SetPosY(int y) { PosY = y; }
	void SetMonsterImage(cImage* Image) { MonsterImage = Image; }
	void SetTerrain(cImage* terrain) { Terrain = terrain; }
	void SetHP(int mon_hp) { HP = mon_hp; }
	void SetATK(int mon_atk) { ATK = mon_atk; }
	void SetDEF(int mon_def) { DEF = mon_def; }
	void SetEXP(int mon_exp) { EXP = mon_exp; }
	void SetMoney(int mon_money) { MONEY = mon_money; }
	void SetIsDie(bool mon_die) { isDie = mon_die; }
	void SetIsHit(bool mon_hit) { isHit = mon_hit; }
	void SetIsDivain(bool mon_divain) { isDivain = mon_divain; }
	void SetPushDir(int dir) { PushDir = dir; }
#pragma endregion
};

