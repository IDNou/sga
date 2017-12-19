#pragma once
#include "cPlayer.h"
#include "cItem.h"

#define MessageWidth 15
#define MessegeHeight 20

class cStore
{
private:
	cPlayer* Player;
	cImage* EmptyBuffer;
	cImage* CommunicationBox;
	cImage* Finger;
	vector<cItem*> vec_Item;

	int InvenMagin;
	int StoreMagin;
	int count;

	bool isSell;
	bool isNotBuy;

public:
	cStore();
	~cStore();

	void Setup();
	void Update();
	void Render(HDC hdc);
};

