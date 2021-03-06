#pragma once

enum ItemType
{
	Type_Consum = 0,
	Type_Sword,
	Type_Amor,
	Type_End
};

class cItem
{
private:
	string name;
	cImage* Image;
	ItemType Type;
	int ATK;
	int DEF;
	int HP;
	int amount;
	int Price;
	bool isWearSword;
	bool isWearAmor;

public:
	cItem();
	~cItem();

	void Setup();
	void Update();
	void Render(HDC hdc);


	void SetupItem(string name, cImage* img, ItemType type, int atk, int def, int hp, int price);

	string GetName() { return name; }
	cImage* GetImage() { return Image; }
	ItemType GetType() { return Type; }
	int GetATK() { return ATK; }
	int GetDEF() { return DEF; }
	int GetHP() { return HP; }
	int GetPrice() { return Price; }
	int GetAmount() { return amount; }
	bool GetIsWearSword() { return isWearSword; }
	bool GetIsWearAmor() { return isWearAmor; }

	void SetName(string item_name) { name = item_name; }
	void SetImage(cImage* item_image) { Image = item_image; }
	void SetType(ItemType item_type) { Type = item_type; }
	void SetATK(int item_atk) { ATK = item_atk; }
	void SetDEF(int item_def) { DEF = item_def; }
	void SetHP(int item_hp) { HP = item_hp; }
	void SetPrice(int item_price) { Price = item_price; }
	void SetAmount(int item_amount) { amount = item_amount; }
	void SetIsWearSword(bool item_isWearSword) { isWearSword = item_isWearSword; }
	void SetIsWearAmor(bool item_isWearAmor) { isWearAmor = item_isWearAmor; }
};

