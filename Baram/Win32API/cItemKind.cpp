#include "stdafx.h"
#include "cItemKind.h"


cItemKind::cItemKind()
{
}


cItemKind::~cItemKind()
{
}

void cItemKind::Setup()
{
}

void cItemKind::Update()
{
	cout << g_pItemManager->FindItem("��")->ATK << endl;
}

void cItemKind::Render()
{
}
