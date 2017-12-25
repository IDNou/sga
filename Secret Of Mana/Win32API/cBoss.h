#pragma once

class cPlayer;

enum TagBossDir {
	Boss_Left = 0,
	Boss_Right,
	Boss_Up,
	Boss_Down,
	Boss_End
};

class cBoss
{
private:
	cImage* BossImage;
	cPlayer* Player;
	cImage* Terrain;
	json BossList;

	RECT SeachRect;

	float PosX;
	float PosY;
	int Boss_FrameX;
	int Boss_FrameY;

	int HP;
	int ATK;
	int DEF;
	int EXP;
	int MONEY;

	POINT LProve;
	POINT RProve;
	POINT TProve;
	POINT BProve;

	TagBossDir Direction;

	int AlphaValue;
	int DivainCount;
	int DamageBuffer;
	int MoveDelay;
	int DirDelay;
	int AttackDelay;
	int AttackCount;
	int Angle;

	bool isShowAttackRect;
	bool isSeachMode;
	bool isMoveStart;
	bool isAttacking;
	bool isAttackMode;
	bool isHit;
	bool isDivain;
	bool AlphaPlag;

public:
	cBoss();
	~cBoss();

	void Setup();
	void Update();
	void Render(HDC hdc);

#pragma region Get
	cImage* &GetBossImage() { return BossImage; }
	float GetPosX() { return PosX; }
	float GetPosY() { return PosY; }
	POINT GetLProve() { return LProve; }
	POINT GetRProve() { return RProve; }
	POINT GetTProve() { return TProve; }
	POINT GetBProve() { return BProve; }
	RECT GetSeachRect() { return SeachRect; }
	TagBossDir GetDir() { return Direction; }
	int GetHP() { return HP; }
	int GetEXP() { return EXP; }
	int GetDEF() { return DEF; }
	int GetATK() { return ATK; }
	int GetMONEY() { return MONEY; }
	int GetFrameX() { return Boss_FrameX; }
	int GetFrameY() { return Boss_FrameY; }
	int GetDamageBuffer() { return DamageBuffer; }
	bool GetIsHit() { return isHit; }
	bool GetIsDivain() { return isDivain; }
	bool GetIsAttackMode() { return isAttackMode; }
	bool GetIsSeachMode() { return isSeachMode; }
	bool GetIsAttacking() { return isAttacking; }
	bool GetIsShowAttackRect() { return isShowAttackRect; }
#pragma endregion
#pragma region Set
	void SetBossImage(cImage* Image) { BossImage = Image; }
	void SetTerrain(cImage* terrain) { Terrain = terrain; }
	void SetPosX(float x) { PosX = x; }
	void SetPosY(float y) { PosY = y; }
	void SetHP(int boss_hp) { HP = boss_hp; }
	void SetATK(int boss_atk) { ATK = boss_atk; }
	void SetDEF(int boss_def) { DEF = boss_def; }
	void SetEXP(int boss_exp) { EXP = boss_exp; }
	void SetMoney(int boss_money) { MONEY = boss_money; }
	void SetLProve(POINT boss_LP) { LProve = boss_LP; }
	void SetRProve(POINT boss_RP) { RProve = boss_RP; }
	void SetTProve(POINT boss_TP) { TProve = boss_TP; }
	void SetBProve(POINT boss_BP) { BProve = boss_BP; }
	void SetSeachRect(RECT boss_seachrect) { SeachRect = boss_seachrect; }
	void SetDir(TagBossDir boss_dir) { Direction = boss_dir; }
	void SetFrameX(int x) { Boss_FrameX = x; }
	void SetFrameY(int y) { Boss_FrameY = y; }
	void SetIsHit(bool boss_ishit) { isHit = boss_ishit; }
	void SetIsDivain(bool boss_isdivain) { isDivain = boss_isdivain; }
	void SetIsAttackMode(bool boss_attackmode) { isAttackMode = boss_attackmode; }
	void SetIsAttacking(bool boss_attacking) { isAttacking = boss_attacking; }
	void SetIsSeachMode(bool boss_seachmode) { isSeachMode = boss_seachmode; }
	void SetIsShowAttackRect(bool boss_showattackrect) { isShowAttackRect = boss_showattackrect; }
	void SetDamageBuffer(int boss_damagebuffer) { DamageBuffer = boss_damagebuffer; }
#pragma endregion
};

