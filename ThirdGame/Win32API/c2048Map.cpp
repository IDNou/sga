#include "stdafx.h"
#include "c2048Map.h"
#include "c2048Player.h"
#include "c2048Object.h"


c2048Map::c2048Map()
{
	m_pImgMap = g_pImageManager->FindImage("Map");
	m_pImgMapBuffer = g_pImageManager->FindImage("MapBuffer");
}

c2048Map::~c2048Map()
{
}

void c2048Map::Setup()
{
}

void c2048Map::Update()
{
}

void c2048Map::Render()
{
}