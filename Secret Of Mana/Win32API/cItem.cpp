#include "stdafx.h"
#include "cItem.h"


cItem::cItem()
{
}


cItem::~cItem()
{
}

void cItem::Setup()
{
}

void cItem::Update()
{
}

void cItem::Render(HDC hdc)
{
}

void cItem::SetupItem(string s_name, cImage * s_img, ItemType s_type, int s_atk, int s_def, int s_hp, int s_price)
{
	name = s_name;
	Image = s_img;
	Type = s_type;
	ATK = s_atk;
	DEF = s_def;
	HP = s_hp;
	Price = s_price;
	amount = 1;
	isWearSword = false;
	isWearAmor = false;
}
