#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"
#include "cMonster.h"


void cPlayScene::Setup()
{
	ifstream PlayerPlace;
	PlayerPlace.open("PlayerPlace.json");
	PlayerPlace >> Place;
	PlayerPlace.close();

	BackGround = g_pImageManager->FindImage("StartVillage");
	BackGround_Magenta = g_pImageManager->FindImage("StartVillage_Magenta");
	EmptyBuffer = g_pImageManager->FindImage("EmptyBuffer");

	CreateTime = 500;

	Player = g_pPlayerManager->GetPlayer();
	if (Place["Place"]["NAME"] == "STORE")
	{
		Player->SetPosX(1085);
		Player->SetPosY(1150);
	}
	else if (Place["Place"]["NAME"] == "WATER")
	{
		Player->SetPosX(1180);
		Player->SetPosY(1390);
	}
	else
	{
		Player->SetPosX(330);
		Player->SetPosY(50);
	}
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetPosX(810);
	Monster->SetPosY(380);
	Monster->SetArea((int)Village_One);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Village_One, Monster));

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetPosX(1030);
	Monster->SetPosY(460);
	Monster->SetArea((int)Village_Two);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Village_Two, Monster));

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetPosX(1200);
	Monster->SetPosY(270);
	Monster->SetArea((int)Village_Three);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Village_Three, Monster));

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetPosX(1030);
	Monster->SetPosY(730);
	Monster->SetArea((int)Village_Four);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Village_Four, Monster));

	g_pSoundManager->Play("FieldSound");
}

void cPlayScene::Update()
{
	Player->Update();
	ViewPort = ViewPortMake(Player->GetPosX(), Player->GetPosY(), WINSIZEX/2, WINSIZEY/2, BackGround->GetWidth(), BackGround->GetHeight());
	Player->SetViewPort(ViewPort);

	//몬스터 젠
	if (CreateTime < 0)
	{
		CreateTime = 500;
		if (map_Monster.size() < 4)
		{
			if (map_Monster.find(Village_One) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetRabit();
				Monster->SetPosX(810);
				Monster->SetPosY(380);
				Monster->SetArea((int)Village_One);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Village_One, Monster));
			}
			if (map_Monster.find(Village_Two) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetRabit();
				Monster->SetPosX(1030);
				Monster->SetPosY(460);
				Monster->SetArea((int)Village_Two);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Village_Two, Monster));
			}
			if (map_Monster.find(Village_Three) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetRabit();
				Monster->SetPosX(1200);
				Monster->SetPosY(270);
				Monster->SetArea((int)Village_Three);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Village_Three, Monster));
			}
			if (map_Monster.find(Village_Four) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetRabit();
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
	}

	// 몬스터 범위안에 들어왔을때
	RECT at;
	for (auto iter = map_Monster.begin(); iter != map_Monster.end(); iter++)
	{
		//밀기
		if (IntersectRect(&at,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
				Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
			&RectMakeCenter(iter->second->GetPosX() + iter->second->GetMonsterImage()->GetFrameWidth() / 2,
				iter->second->GetPosY() + iter->second->GetMonsterImage()->GetFrameHeight() / 2, 20, 20)))
		{
			switch (Player->GetPlayerDir())
			{
			case LEFT:
				Player->SetPosX(Player->GetPosX() + ((at.right - at.left) + 4));
				break;
			case RIGHT:
				Player->SetPosX(Player->GetPosX() - ((at.right - at.left) + 4));
				break;
			case UP:
				Player->SetPosY(Player->GetPosY() + ((at.bottom - at.top) + 5));
				break;
			case DOWN:
				Player->SetPosY(Player->GetPosY() - ((at.bottom - at.top) + 5));
				break;
			}
			Player->SetMonster(iter->second);
			Player->SetIsPush(true);
		}

		//추적 및 공격
		if (!iter->second->GetIsDivain()) 
		{

			// 실질적 공격로직
			if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
				&RectMakeCenter(iter->second->GetLProve().x, iter->second->GetLProve().y, 15, 30)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
			{
				Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
				Player->SetisDivain(true);
				Player->SetIsHit(true);
				Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
				Player->SetPlayerDir((PlayerDir) 1);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
				&RectMakeCenter(iter->second->GetRProve().x, iter->second->GetRProve().y, 15, 30)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
			{
				Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
				Player->SetisDivain(true);
				Player->SetIsHit(true);
				Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
				Player->SetPlayerDir((PlayerDir) 0);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
				&RectMakeCenter(iter->second->GetTProve().x, iter->second->GetTProve().y, 30, 15)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
			{
				Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
				Player->SetisDivain(true);
				Player->SetIsHit(true);
				Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
				Player->SetPlayerDir((PlayerDir)3);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
				&RectMakeCenter(iter->second->GetBProve().x, iter->second->GetBProve().y, 30, 15)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
			{
				Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
				Player->SetisDivain(true);
				Player->SetIsHit(true);
				Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
				Player->SetPlayerDir((PlayerDir)2);
			}
			

			//공격모션을 취해라
			if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
				&RectMakeCenter(iter->second->GetLProve().x, iter->second->GetLProve().y, 15, 30)) && !iter->second->GetIsAttackMode())
			{
				iter->second->SetDir(MON_LEFT);
				iter->second->SetFrameX(0);
				iter->second->SetIsAttacking(true);
				iter->second->SetIsAttackMode(true);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
				&RectMakeCenter(iter->second->GetRProve().x, iter->second->GetRProve().y, 15, 30)) && !iter->second->GetIsAttackMode())
			{
				iter->second->SetDir(MON_RIGHT);
				iter->second->SetFrameX(0);
				iter->second->SetIsAttacking(true);
				iter->second->SetIsAttackMode(true);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
				&RectMakeCenter(iter->second->GetTProve().x, iter->second->GetTProve().y, 30, 15)) && !iter->second->GetIsAttackMode())
			{
				iter->second->SetDir(MON_UP);
				iter->second->SetFrameX(0);
				iter->second->SetIsAttacking(true);
				iter->second->SetIsAttackMode(true);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
				&RectMakeCenter(iter->second->GetBProve().x, iter->second->GetBProve().y, 30, 15)) && !iter->second->GetIsAttackMode())
			{
				iter->second->SetDir(MON_DOWN);
				iter->second->SetFrameX(0);
				iter->second->SetIsAttacking(true);
				iter->second->SetIsAttackMode(true);
			}
			// 추적
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
					Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10),
				&iter->second->GetSeachRect()))
			{
				SeachTime = 200;
				iter->second->SetIsSeachMode(true);
			}
			//추적 끝
			else if (!IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
					Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10),
				&iter->second->GetSeachRect()))
			{
				if (SeachTime < 0)
				{
					iter->second->SetIsSeachMode(false);
				}
			}
		}
	}

	//플레이어 공격시
	RECT rt;
	for (auto iter = map_Monster.begin(); iter != map_Monster.end(); iter++)
	{
		if (IntersectRect(&rt, &Player->GetAttackRange(),
			&RectMakeCenter(iter->second->GetPosX() + iter->second->GetMonsterImage()->GetFrameWidth() / 2, iter->second->GetPosY() + iter->second->GetMonsterImage()->GetFrameHeight() / 2, 20, 20))
			&& !iter->second->GetIsDivain())
		{
			if (!iter->second->GetIsHit())
			{
				iter->second->SetIsHit(true);
				iter->second->SetPushDir((int)Player->GetPlayerDir());
				iter->second->SetIsDivain(true);
				iter->second->SetIsAttackMode(false);
				iter->second->SetIsAttacking(false);
				iter->second->SetHP(iter->second->GetHP() - (Player->GetATK() + Player->GetItemATK() - iter->second->GetDEF()));
				iter->second->SetDamageBuffer((Player->GetATK() + Player->GetItemATK() - iter->second->GetDEF()));
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
		g_pSceneManager->SetNextScene(SLIST_WATERPATH);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (IntersectRect(&ct,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10),
		&RectMake(1085, 1110, 15, 15)))
	{
		g_pSceneManager->SetNextScene(SLIST_HOUSE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	if (g_pKeyManager->isStayKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	/*if (Player->GetHP() <= 0)
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}*/

	SeachTime--;
	CreateTime--;
}


void cPlayScene::Render()
{
	BackGround->Render(EmptyBuffer->GetMemDC());
	for (auto iter = map_Monster.begin(); iter != map_Monster.end(); iter++)
	{
		iter->second->Render(EmptyBuffer->GetMemDC());
	}
	Player->Render(EmptyBuffer->GetMemDC());
	//RectangleMake(EmptyBuffer->GetMemDC(), 1180, 1430, 35, 25);
	//RectangleMake(EmptyBuffer->GetMemDC(), 1085, 1110, 15, 15);
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort, WINSIZEX, WINSIZEY);
}

void cPlayScene::Release()
{
	m_vMonster.clear();
}
