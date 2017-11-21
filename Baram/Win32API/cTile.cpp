#include "stdafx.h"
#include "cTile.h"


cTile::cTile()
{

}


cTile::~cTile()
{
}

tagTile cTile::CreateDefaultTiles(int x, int y)
{
	tagTile newTile;

	newTile.fPosX = 20 + 40 * x;
	newTile.fPosY = 20 + 40 * y;
	newTile.alpha = 0;
	newTile.alpha2 = 0;
	newTile.isMove = true;
	newTile.rtTile= RectMakeCenter(newTile.fPosX, newTile.fPosY, 40, 40);
	return newTile;
}

tagTile cTile::SettingTiles(int AlphaHeight, int AlphaVolume, bool isMove)
{
	tagTile newTile;

	newTile.alpha = AlphaHeight;
	newTile.alpha2 = AlphaVolume;
	newTile.isMove = isMove;

	return newTile;
}
bool cTile::SettingTilesNoMove()
{
	return false;
}

bool cTile::SettingTilesMove()
{
	return true;
}



