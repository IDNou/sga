#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"
#include "cMonster.h"


void cPlayScene::Setup()
{
	BackGround = g_pImageManager->FindImage("StartVillage");
	BackGround_Magenta = g_pImageManager->FindImage("StartVillage_Magenta");
	EmptyBuffer = g_pImageManager->FindImage("EmptyBuffer");

	Player = g_pPlayerManager->GetPlayer();
	Player->SetPosX(1180);
	Player->SetPosY(1350);
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);
	Player->SetTerrainWidth(BackGround->GetWidth());
	Player->SetTerrainHeight(BackGround->GetHeight());

	json MonsterList;
	ifstream json_List;
	json_List.open("MonsterList.json");
	json_List >> MonsterList;
	json_List.close();

	
	Monster = new cMonster;
	Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
	Monster->SetPosX(810);
	Monster->SetPosY(380);
	Monster->Setup();
	Monster->SetHP(MonsterList["Rabit"]["HP"]);
	Monster->SetATK(MonsterList["Rabit"]["ATK"]);
	Monster->SetDEF(MonsterList["Rabit"]["DEF"]);
	Monster->SetEXP(MonsterList["Rabit"]["EXP"]);
	Monster->SetTerrain(BackGround_Magenta);
	m_vMonster.push_back(Monster);

	/*Monster = new cMonster;
	Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
	Monster->SetPosX(1030);
	Monster->SetPosY(460);
	Monster->Setup();
	Monster->SetHP(MonsterList["Rabit"]["HP"]);
	Monster->SetATK(MonsterList["Rabit"]["ATK"]);
	Monster->SetDEF(MonsterList["Rabit"]["DEF"]);
	Monster->SetEXP(MonsterList["Rabit"]["EXP"]);
	Monster->SetTerrain(BackGround_Magenta);
	m_vMonster.push_back(Monster);

	Monster = new cMonster;
	Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
	Monster->SetPosX(1200);
	Monster->SetPosY(270);
	Monster->Setup();
	Monster->SetHP(MonsterList["Rabit"]["HP"]);
	Monster->SetATK(MonsterList["Rabit"]["ATK"]);
	Monster->SetDEF(MonsterList["Rabit"]["DEF"]);
	Monster->SetEXP(MonsterList["Rabit"]["EXP"]);
	Monster->SetTerrain(BackGround_Magenta);
	m_vMonster.push_back(Monster);

	Monster = new cMonster;
	Monster->SetMonsterImage(g_pImageManager->FindImage("Rabit"));
	Monster->SetPosX(1030);
	Monster->SetPosY(730);
	Monster->Setup();
	Monster->SetHP(MonsterList["Rabit"]["HP"]);
	Monster->SetATK(MonsterList["Rabit"]["ATK"]);
	Monster->SetDEF(MonsterList["Rabit"]["DEF"]);
	Monster->SetEXP(MonsterList["Rabit"]["EXP"]);
	Monster->SetTerrain(BackGround_Magenta);
	m_vMonster.push_back(Monster);*/


	g_pSoundManager->Play("FieldSound");
}

void cPlayScene::Update()
{
	Player->Update();
	ViewPort = ViewPortMake(Player->GetPosX(), Player->GetPosY(), WINSIZEX/2, WINSIZEY/2, BackGround->GetWidth(), BackGround->GetHeight());
	Player->SetViewPort(ViewPort);

	for (auto iter = m_vMonster.begin(); iter != m_vMonster.end(); iter++)
		(*iter)->Update();

	//공격시
	RECT rt;
	for (auto iter = m_vMonster.begin(); iter != m_vMonster.end(); iter++)
	{
		if (IntersectRect(&rt, &Player->GetAttackRange(),
			&RectMakeCenter((*iter)->GetPosX() + (*iter)->GetMonster()->GetFrameWidth() / 2, (*iter)->GetPosY() + (*iter)->GetMonster()->GetFrameHeight() / 2, 20, 20))
			&& !(*iter)->GetIsDivain())
		{
			if (!(*iter)->GetIsHit())
			{
				(*iter)->SetIsHit(true);
				(*iter)->SetPushDir((int)Player->GetPlayerDir());
				(*iter)->SetIsDivain(true);
				(*iter)->SetHP((*iter)->GetHP() - (Player->GetATK() - (*iter)->GetDEF()));
				if ((*iter)->GetHP() <= 0)
				{
					Player->SetEXP(Player->GetEXP() + (*iter)->GetEXP());
					Player->SetMONEY(Player->GetMoney() + (*iter)->GetMONEY());
					(*iter)->SetIsDie(true);
				}
			}
		}

		//공격플래그 초기화
		if (!Player->GetIsAttack())
		{
			(*iter)->SetIsHit(false);
		}
	}

	//사망처리
	for (auto iter = m_vMonster.begin(); iter != m_vMonster.end(); )
	{
		if ((*iter)->GetIsDie())
			iter = m_vMonster.erase(iter);
		else
			iter++;
	}

	RECT ct;
	if (IntersectRect(&ct,
		&RectMake(Player->GetPosX(),Player->GetPosY(),Player->GetPlayerImage()->GetFrameWidth(),Player->GetPlayerImage()->GetFrameHeight()),
		&RectMake(1180,1430,35,25)))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_WATERPATH);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (IntersectRect(&ct,
		&RectMake(Player->GetPosX(), Player->GetPosY(),30,30),
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
}


void cPlayScene::Render()
{
	BackGround->Render(EmptyBuffer->GetMemDC());
	Player->Render(EmptyBuffer->GetMemDC());
	for (auto iter = m_vMonster.begin(); iter != m_vMonster.end(); iter++)
	{
		(*iter)->Render(EmptyBuffer->GetMemDC());
	}
	RectangleMakeCenter(EmptyBuffer->GetMemDC(), Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth()/2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10,10);
	RectangleMake(EmptyBuffer->GetMemDC(), 1180, 1430, 35, 25);
	RectangleMake(EmptyBuffer->GetMemDC(), 1085, 1110, 15, 15);
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort, WINSIZEX, WINSIZEY);
}

void cPlayScene::Release()
{
}
