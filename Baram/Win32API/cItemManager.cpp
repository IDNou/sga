#include "stdafx.h"
#include "cItemManager.h"

tagItemInfo* cItemManager::AddItem(string key, ItemType Type, int HP, int MP, int ATK, int DEF, int STR, int INT, int AGL, int price, int LimitLV)
{
	tagItemInfo* item = FindItem(key);

	if (item == NULL)
	{
		item = new tagItemInfo;
		
		item->LimitLV = LimitLV;
		item->ATK = ATK;
		item->DEF = DEF;
		item->HP = HP;
		item->MP = MP;
		item->STR = STR;
		item->INT = INT;
		item->AGL = AGL;
		item->PRICE = price;
		item->type = Type;

		MapItem.insert(make_pair(key, item));
	}

	return item;
}

tagItemInfo* cItemManager::FindItem(string key)
{
	itemIter = MapItem.find(key);

	if (itemIter != MapItem.end())
	{
		return itemIter->second;
	}

	return NULL;
}
