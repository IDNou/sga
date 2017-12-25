#include "stdafx.h"
#include "cBossScene.h"
#include "cPlayer.h"
#include "cMonster.h"

void cBossScene::Setup()
{
	SeachTime = 0;

	BackGround = g_pImageManager->FindImage("BossMap");
	BackGround_Magenta = g_pImageManager->FindImage("BossMap_Magenta");
	EmptyBuffer = g_pImageManager->FindImage("EmptyBuffer");

	Player = g_pPlayerManager->GetPlayer();
	Player->SetPosX(310);
	Player->SetPosY(230);
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);
	
	Boss = new cBoss;
	Boss->SetPosX(200);
	Boss->SetPosY(120);
	Boss->Setup();
	Boss->SetTerrain(BackGround_Magenta);
}

void cBossScene::Update()
{
	Player->Update();
	ViewPort = ViewPortMake(Player->GetPosX(), Player->GetPosY(), WINSIZEX / 2, WINSIZEY / 2, BackGround->GetWidth(), BackGround->GetHeight());
	Player->SetViewPort(ViewPort);

	Boss->Update();

	RECT rt;
	//밀기
	if (IntersectRect(&rt,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
		&RectMakeCenter(Boss->GetPosX() + Boss->GetBossImage()->GetFrameWidth() / 2,
			Boss->GetPosY() + Boss->GetBossImage()->GetFrameHeight() / 2, 20, 20)))
	{
		switch (Player->GetPlayerDir())
		{
		case LEFT:
			Player->SetPosX(Player->GetPosX() + ((rt.right - rt.left) + 4));
			break;
		case RIGHT:
			Player->SetPosX(Player->GetPosX() - ((rt.right - rt.left) + 4));
			break;
		case UP:
			Player->SetPosY(Player->GetPosY() + ((rt.bottom - rt.top) + 5));
			break;
		case DOWN:
			Player->SetPosY(Player->GetPosY() - ((rt.bottom - rt.top) + 5));
			break;
		}
		Player->SetBoss(Boss);
		Player->SetIsPush(true);
	}

	//추적 및 공격
	if (!Boss->GetIsDivain())
	{

		// 실질적 공격로직
		if (IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
			&RectMakeCenter(Boss->GetLProve().x, Boss->GetLProve().y, 15, 30)) && Boss->GetIsShowAttackRect() && !Player->GetIsDivain())
		{
			Player->SetHp(Player->GetHP() - Boss->GetATK() + Player->GetDEF());
			Player->SetisDivain(true);
			Player->SetIsHit(true);
			Player->SetDamageBuffer(Boss->GetATK() + Player->GetDEF());
			Player->SetPlayerDir((PlayerDir)1);
		}
		else if (IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
			&RectMakeCenter(Boss->GetRProve().x, Boss->GetRProve().y, 15, 30)) && Boss->GetIsShowAttackRect() && !Player->GetIsDivain())
		{
			Player->SetHp(Player->GetHP() - Boss->GetATK() + Player->GetDEF());
			Player->SetisDivain(true);
			Player->SetIsHit(true);
			Player->SetDamageBuffer(Boss->GetATK() + Player->GetDEF());
			Player->SetPlayerDir((PlayerDir)0);
		}
		else if (IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
			&RectMakeCenter(Boss->GetTProve().x, Boss->GetTProve().y, 30, 15)) && Boss->GetIsShowAttackRect() && !Player->GetIsDivain())
		{
			Player->SetHp(Player->GetHP() - Boss->GetATK() + Player->GetDEF());
			Player->SetisDivain(true);
			Player->SetIsHit(true);
			Player->SetDamageBuffer(Boss->GetATK() + Player->GetDEF());
			Player->SetPlayerDir((PlayerDir)3);
		}
		else if (IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
			&RectMakeCenter(Boss->GetBProve().x, Boss->GetBProve().y, 30, 15)) && Boss->GetIsShowAttackRect() && !Player->GetIsDivain())
		{
			Player->SetHp(Player->GetHP() - Boss->GetATK() + Player->GetDEF());
			Player->SetisDivain(true);
			Player->SetIsHit(true);
			Player->SetDamageBuffer(Boss->GetATK() + Player->GetDEF());
			Player->SetPlayerDir((PlayerDir)2);
		}


		//공격모션을 취해라
		if (IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
			&RectMakeCenter(Boss->GetLProve().x, Boss->GetLProve().y, 15, 30)) && !Boss->GetIsAttackMode())
		{
			Boss->SetDir(Boss_Left);
			Boss->SetFrameX(1);
			Boss->SetIsAttacking(true);
			Boss->SetIsAttackMode(true);
		}
		else if (IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
			&RectMakeCenter(Boss->GetRProve().x, Boss->GetRProve().y, 15, 30)) && !Boss->GetIsAttackMode())
		{
			Boss->SetDir(Boss_Right);
			Boss->SetFrameX(1);
			Boss->SetIsAttacking(true);
			Boss->SetIsAttackMode(true);
		}
		else if (IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
			&RectMakeCenter(Boss->GetTProve().x, Boss->GetTProve().y, 30, 15)) && !Boss->GetIsAttackMode())
		{
			Boss->SetDir(Boss_Up);
			Boss->SetFrameX(1);
			Boss->SetIsAttacking(true);
			Boss->SetIsAttackMode(true);
		}
		else if (IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 25),
			&RectMakeCenter(Boss->GetBProve().x, Boss->GetBProve().y, 30, 15)) && !Boss->GetIsAttackMode())
		{
			Boss->SetDir(Boss_Down);
			Boss->SetFrameX(1);
			Boss->SetIsAttacking(true);
			Boss->SetIsAttackMode(true);
		}
		// 추적
		else if (IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
				Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10),
			&Boss->GetSeachRect()))
		{
			SeachTime = 200;
			Boss->SetIsSeachMode(true);
		}
		//추적 끝
		else if (!IntersectRect(&rt,
			&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
				Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10),
			&Boss->GetSeachRect()))
		{
			if (SeachTime < 0)
			{
				Boss->SetIsSeachMode(false);
			}
		}
	}
	if (IntersectRect(&rt, &Player->GetAttackRange(),
		&RectMakeCenter(Boss->GetPosX() + Boss->GetBossImage()->GetFrameWidth() / 2, Boss->GetPosY() + Boss->GetBossImage()->GetFrameHeight() / 2, 40, 40))
		&& !Boss->GetIsDivain())
	{
		Boss->SetIsHit(true);
		Boss->SetIsDivain(true);
		Boss->SetDir((TagBossDir)Player->GetPlayerDir());
		Boss->SetHP(Boss->GetHP() - (Player->GetATK() + Player->GetItemATK() - Boss->GetDEF()));
		Boss->SetDamageBuffer(Player->GetATK() + Player->GetItemATK() - Boss->GetDEF());
	}

	if (!Player->GetIsAttack())
	{
		Boss->SetIsHit(false);
	}

	if (Boss->GetHP() <= 0)
	{
		Player->SetEXP(Player->GetEXP() + Boss->GetEXP());
		Player->SetMONEY(Player->GetMoney() + Boss->GetMONEY());
		/*g_pSceneManager->SetNextScene(SLIST_ENDING);
		g_pSceneManager->ChangeScene(SLIST_LOADING);*/
	}

	if (g_pKeyManager->isStayKeyDown(VK_ESCAPE))
	{
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
}

void cBossScene::Render()
{
	BackGround->Render(EmptyBuffer->GetMemDC());
	Player->Render(EmptyBuffer->GetMemDC());
	Boss->Render(EmptyBuffer->GetMemDC());
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort);
}

void cBossScene::Release()
{
}
