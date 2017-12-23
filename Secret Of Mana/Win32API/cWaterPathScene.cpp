#include "stdafx.h"
#include "cWaterPathScene.h"
#include "cMonster.h"
#include "cPlayer.h"

void cWaterPathScene::Setup()
{

	BackGround = g_pImageManager->FindImage("WaterAndPandoraPath");
	BackGround_Magenta = g_pImageManager->FindImage("WaterAndPandoraPath_Magenta");
	EmptyBuffer = g_pImageManager->FindImage("EmptyBuffer");

	CreateTime = 500;

	Player = g_pPlayerManager->GetPlayer();
	Player->SetPosX(830);
	Player->SetPosY(50);
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetPosX(810);
	Monster->SetPosY(380);
	Monster->SetArea((int)Water_One);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_One, Monster));

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetPosX(1030);
	Monster->SetPosY(460);
	Monster->SetArea((int)Water_Two);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_Two, Monster));

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetPosX(1200);
	Monster->SetPosY(270);
	Monster->SetArea((int)Water_Three);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_Three, Monster));

	Monster = g_pMonsterManager->GetRabit();
	Monster->SetPosX(1030);
	Monster->SetPosY(730);
	Monster->SetArea((int)Water_Four);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_Four, Monster));

	g_pSoundManager->Play("WaterPath");
}

void cWaterPathScene::Update()
{
	Player->Update();
	ViewPort = ViewPortMake(Player->GetPosX(), Player->GetPosY(), WINSIZEX / 2, WINSIZEY / 2, BackGround->GetWidth(), BackGround->GetHeight());
	Player->SetViewPort(ViewPort);


	//몬스터 젠
	if (CreateTime < 0)
	{
		CreateTime = 500;
		if (map_Monster.size() < 4)
		{
			if (map_Monster.find(Water_One) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetBee();
				Monster->SetPosX(810);
				Monster->SetPosY(380);
				Monster->SetArea((int)Water_One);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_One, Monster));
			}
			if (map_Monster.find(Water_Two) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetBee();
				Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
				Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
				Monster->SetPosX(1030);
				Monster->SetPosY(460);
				Monster->SetArea((int)Water_Two);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_Two, Monster));
			}
			if (map_Monster.find(Water_Three) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetBee();
				Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
				Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
				Monster->SetPosX(1200);
				Monster->SetPosY(270);
				Monster->SetArea((int)Water_Three);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_Three, Monster));
			}
			if (map_Monster.find(Water_Four) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetBee();
				Monster->SetFrameX(g_pImageManager->FindImage("Rabit")->GetFrameX());
				Monster->SetFrameY(g_pImageManager->FindImage("Rabit")->GetFrameY());
				Monster->SetPosX(1030);
				Monster->SetPosY(730);
				Monster->SetArea((int)Water_Four);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_Four, Monster));
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
		//추적 및 공격
		if (!iter->second->GetIsDivain())
		{

			//밀기
			if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
					Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(iter->second->GetPosX() + iter->second->GetMonsterImage()->GetFrameWidth() / 2,
					iter->second->GetPosY() + iter->second->GetMonsterImage()->GetFrameHeight() / 2, 20, 20)))
			{
				switch (Player->GetPlayerDir())
				{
				case LEFT:
					Player->SetPosX(Player->GetPosX() + (at.right - at.left));
					break;
				case RIGHT:
					Player->SetPosX(Player->GetPosX() - (at.right - at.left));
					break;
				case UP:
					Player->SetPosY(Player->GetPosY() + (at.bottom - at.top));
					break;
				case DOWN:
					Player->SetPosY(Player->GetPosY() - (at.bottom - at.top));
					break;
				}
				Player->SetMonster(iter->second);
				Player->SetIsPush(true);
			}

			// 실질적 공격로직
			if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(iter->second->GetLProve().x - 10, iter->second->GetLProve().y, 15, 30)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
			{
				Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
				Player->SetisDivain(true);
				Player->SetIsHit(true);
				Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
				Player->SetPlayerDir((PlayerDir)0);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(iter->second->GetRProve().x + 10, iter->second->GetRProve().y, 15, 30)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
			{
				Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
				Player->SetisDivain(true);
				Player->SetIsHit(true);
				Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
				Player->SetPlayerDir((PlayerDir)1);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(iter->second->GetTProve().x, iter->second->GetTProve().y - 10, 15, 30)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
			{
				Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
				Player->SetisDivain(true);
				Player->SetIsHit(true);
				Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
				Player->SetPlayerDir((PlayerDir)2);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(iter->second->GetBProve().x, iter->second->GetBProve().y + 10, 15, 30)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
			{
				Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
				Player->SetisDivain(true);
				Player->SetIsHit(true);
				Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
				Player->SetPlayerDir((PlayerDir)3);
			}


			//공격모션을 취해라
			if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(iter->second->GetLProve().x - 10, iter->second->GetLProve().y, 15, 30)) && !iter->second->GetIsAttackMode())
			{
				iter->second->SetDir(MON_LEFT);
				iter->second->SetFrameX(0);
				iter->second->SetIsAttacking(true);
				iter->second->SetIsAttackMode(true);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(iter->second->GetRProve().x + 10, iter->second->GetRProve().y, 15, 30)) && !iter->second->GetIsAttackMode())
			{
				iter->second->SetDir(MON_RIGHT);
				iter->second->SetFrameX(0);
				iter->second->SetIsAttacking(true);
				iter->second->SetIsAttackMode(true);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(iter->second->GetTProve().x, iter->second->GetTProve().y - 10, 15, 30)) && !iter->second->GetIsAttackMode())
			{
				iter->second->SetDir(MON_UP);
				iter->second->SetFrameX(0);
				iter->second->SetIsAttacking(true);
				iter->second->SetIsAttackMode(true);
			}
			else if (IntersectRect(&at,
				&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 34),
				&RectMakeCenter(iter->second->GetBProve().x, iter->second->GetBProve().y + 10, 15, 30)) && !iter->second->GetIsAttackMode())
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


	RECT qt;
	if (IntersectRect(&qt,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10), 
		&RectMake(670, 1650, 35, 25)))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_BOSSMAP);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (IntersectRect(&qt,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10),
		&RectMake(810, 0, 40, 30)))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_PLAY);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	if (g_pKeyManager->isStayKeyDown(VK_ESCAPE))
	{
		m_vMonster.clear();
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	SeachTime--;
	CreateTime--;
}

void cWaterPathScene::Render()
{
	BackGround->Render(EmptyBuffer->GetMemDC());
	for (auto iter = map_Monster.begin(); iter != map_Monster.end(); iter++)
	{
		iter->second->Render(EmptyBuffer->GetMemDC());
	}
	Player->Render(EmptyBuffer->GetMemDC());
	RectangleMake(EmptyBuffer->GetMemDC(), 670, 1650, 30, 20);
	RectangleMake(EmptyBuffer->GetMemDC(), 810, 0, 40, 30);
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort, WINSIZEX, WINSIZEY);
}

void cWaterPathScene::Release()
{
	m_vMonster.clear();
}
