#pragma once
#include "cSingletonBase.h"
#include "cItem.h"

#define g_pItemManager cItemManager::GetInstance()

class cItemManager : public cSingletonBase<cItemManager>
{
private:
	map<string, cItem*>			m_mapItem;
	map<string, cItem*>::iterator	m_mapIter;
	json ItemList;

public:
	cItemManager();
	~cItemManager();

	void Start();
	void Update();
	void Render();

	cItem* ItemAdd(string key, cImage* img,ItemType type,int ATK, int DEF, int HP, int Price);

	cItem* FindItem(string key);		// 아이템 찾기
	void ItemRelease(string key);
};