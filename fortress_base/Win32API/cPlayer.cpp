#include "stdafx.h"
#include "cPlayer.h"
#include "cProgressBar.h"
#include "cMap.h"
#include "cObjects.h"


cPlayer::cPlayer()
{
	
}


cPlayer::~cPlayer()
{
	
}

void cPlayer::Setup()
{
	
}

void cPlayer::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
		m_pMap->SetPosXY(500, 500);
	
}

void cPlayer::MiniRender()
{

}


void cPlayer::Render()
{
	
}
