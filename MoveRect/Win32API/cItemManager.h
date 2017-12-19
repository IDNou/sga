#pragma once
#include "cSingletonBase.h"

#define g_pItemManager cItemManager::GetInstance()


enum ItemType
{
	SWORD = 0,
	ARMOUR,
	PORTION,
	END
};

struct tagItemInfo
{
	ItemType	type;
	int			ATK;
	int			DEF;
	int			HP;
	int			MP;
	int			STR;
	int			INT;
	int			AGL;
	int			PRICE;
	int			LimitLV;

	tagItemInfo()
	{
		type = END;
		ATK = 0;
		DEF = 0;
		HP = 0;
		MP = 0;
		STR = 0;
		INT = 0;
		AGL = 0;
		PRICE = 0;
		LimitLV = 0;
	}
};

class cItemManager : public cSingletonBase<cItemManager>
{
private:
	map<string, tagItemInfo*>				MapItem;
	map<string, tagItemInfo*>::iterator		itemIter;
public:
	tagItemInfo* AddItem(string key, ItemType Type, int HP, int MP, int ATK, int DEF, int STR, int INT, int AGL, int price, int LimitLV);
	tagItemInfo* FindItem(string key);
};

