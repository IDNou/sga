#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"
#include "cMonster.h"


void cPlayScene::Setup()
{
	BackGround = g_pImageManager->FindImage("StartVillage");
	BackGround_Magenta = g_pImageManager->FindImage("StartVillage_Magenta");
	EmptyBuffer = g_pImageManager->FindImage("EmptyBuffer");

	CreateTime = 500;

	Player = g_pPlayerManager->GetPlayer();
	Player->SetPosX(800);
	Player->SetPosY(350);
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);
	Player->SetTerrainWidth(BackGround->GetWidth());
	Player->SetTerrainHeight(BackGround->GetHeight());

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
	Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
	Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
	Monster->SetPosX(810);
	Monster->SetPosY(380);
	Monster->SetArea((int)Village_One);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Village_One, Monster));
	//m_vMonster.push_back(Monster);

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
	Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
	Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
	Monster->SetPosX(1030);
	Monster->SetPosY(460);
	Monster->SetArea((int)Village_Two);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Village_Two, Monster));
	//m_vMonster.push_back(Monster);

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
	Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
	Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
	Monster->SetPosX(1200);
	Monster->SetPosY(270);
	Monster->SetArea((int)Village_Three);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Village_Three, Monster));
	//m_vMonster.push_back(Monster);

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
	Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
	Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
	Monster->SetPosX(1030);
	Monster->SetPosY(730);
	Monster->SetArea((int)Village_Four);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Village_Four, Monster));
	//m_vMonster.push_back(Monster);

	g_pSoundManager->Play("FieldSound");
}

void cPlayScene::Update()
{
	Player->Update();
	ViewPort = ViewPortMake(Player->GetPosX(), Player->GetPosY(), WINSIZEX/2, WINSIZEY/2, BackGround->GetWidth(), BackGround->GetHeight());
	Player->SetViewPort(ViewPort);

	if (CreateTime < 0)
	{
		CreateTime = 500;
		if (map_Monster.size() < 4)
		{
			if (map_Monster.find(Village_One) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetRabit();
				Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
				Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
				Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
				Monster->SetPosX(810);
				Monster->SetPosY(380);
				Monster->SetArea((int)Village_One);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Village_One, Monster));
			}
			if (map_Monster.find(Village_Two) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetRabit();
				Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
				Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
				Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
				Monster->SetPosX(1030);
				Monster->SetPosY(460);
				Monster->SetArea((int)Village_Two);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Village_Two, Monster));
			}
			if (map_Monster.find(Village_Three) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetRabit();
				Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
				Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
				Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
				Monster->SetPosX(1200);
				Monster->SetPosY(270);
				Monster->SetArea((int)Village_Three);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Village_Three, Monster));
			}
			if (map_Monster.find(Village_Four) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetRabit();
				Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
				Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
				Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
				Monster->SetPosX(1030);
				Monster->SetPosY(730);
				Monster->SetArea((int)Village_Four);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Village_Four, Monster));
			}
		}
	}

	for (auto iter = map_Monster.begin(); iter != map_Monster.end(); iter++)
	{
		iter->second->Update();
		//(*iter)->Update();
	}

	//공격시
	RECT rt;
	for (auto iter = map_Monster.begin(); iter != map_Monster.end(); iter++)
	{
		if (IntersectRect(&rt, &Player->GetAttackRange(),
			&RectMakeCenter(iter->second->GetPosX() + iter->second->GetMonster()->GetFrameWidth() / 2, iter->second->GetPosY() + iter->second->GetMonster()->GetFrameHeight() / 2, 20, 20))
			&& !iter->second->GetIsDivain())
		{
			if (!iter->second->GetIsHit())
			{
				iter->second->SetIsHit(true);
				iter->second->SetPushDir((int)Player->GetPlayerDir());
				iter->second->SetIsDivain(true);
				iter->second->SetHP(iter->second->GetHP() - (Player->GetATK() + Player->GetItemATK() - iter->second->GetDEF()));
				if (iter->second->GetHP() <= 0)
				{
					Player->SetEXP(Player->GetEXP() + iter->second->GetEXP());
					Player->SetMONEY(Player->GetMoney() + iter->second->GetMONEY());
					iter->second->SetIsDie(true);
				}
			}
		}

		//공격플래그 초기화
		if (!Player->GetIsAttack())
		{
			iter->second->SetIsHit(false);
		}
	}

	//사망처리
	for (auto iter = map_Monster.begin(); iter != map_Monster.end(); )
	{
		if (iter->second->GetIsDie())
		{
			SAFE_DELETE(iter->second);
			iter = map_Monster.erase(iter);
		}
		else
			iter++;
	}

	RECT ct;
	if (IntersectRect(&ct,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10,10,10),
		&RectMake(1180,1430,35,25)))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_WATERPATH);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (IntersectRect(&ct,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10),
		&RectMake(1085, 1110, 15, 15)))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_HOUSE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	if (g_pKeyManager->isStayKeyDown(VK_ESCAPE))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	CreateTime--;
}


void cPlayScene::Render()
{
	BackGround->Render(EmptyBuffer->GetMemDC());
	Player->Render(EmptyBuffer->GetMemDC());
	for (auto iter = map_Monster.begin(); iter != map_Monster.end(); iter++)
	{
		iter->second->Render(EmptyBuffer->GetMemDC());
		//(*iter)->Render(EmptyBuffer->GetMemDC());
	}
	RectangleMakeCenter(EmptyBuffer->GetMemDC(), Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth()/2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10,10);
	RectangleMake(EmptyBuffer->GetMemDC(), 1180, 1430, 35, 25);
	RectangleMake(EmptyBuffer->GetMemDC(), 1085, 1110, 15, 15);
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort, WINSIZEX, WINSIZEY);
}

void cPlayScene::Release()
{
}
