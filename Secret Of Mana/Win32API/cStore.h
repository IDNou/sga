#pragma once
#include "cPlayer.h"
#include "cItem.h"

#define MessageWidth 15
#define MessegeHeight 20

class cStore
{
private:
	//플레이어가 가진 아이템
	cPlayer* Player;
	cImage* EmptyBuffer;
	cImage* CommunicationBox;
	cImage* Finger;
	//진열된 아이템
	vector<cItem*> vec_Item;

	int InvenMagin;
	int StoreMagin;
	int count;

	bool isSell;
	bool isNotBuy;
	bool isOwn;
	bool isConsumOwn;

public:
	cStore();
	~cStore();

	void Setup();
	void Update();
	void Render(HDC hdc);
};

