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
	Player->SetPosX(800);
	Player->SetPosY(40);
	Player->Setup();
	Player->SetTerrain(BackGround_Magenta);

	Monster = g_pMonsterManager->GetBee();
	Monster->SetPosX(830);
	Monster->SetPosY(340);
	Monster->SetArea((int)Water_One);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_One, Monster));

	Monster = g_pMonsterManager->GetBee();
	Monster->SetPosX(840);
	Monster->SetPosY(670);
	Monster->SetArea((int)Water_Two);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_Two, Monster));

	Monster = g_pMonsterManager->GetBee();
	Monster->SetPosX(880);
	Monster->SetPosY(1020);
	Monster->SetArea((int)Water_Three);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_Three, Monster));

	Monster = g_pMonsterManager->GetBee();
	Monster->SetPosX(230);
	Monster->SetPosY(420);
	Monster->SetArea((int)Water_Four);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_Four, Monster));

	Monster = g_pMonsterManager->GetBee();
	Monster->SetPosX(400);
	Monster->SetPosY(1285);
	Monster->SetArea((int)Water_Five);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_Five, Monster));

	Monster = g_pMonsterManager->GetCobolt();
	Monster->SetPosX(190);
	Monster->SetPosY(1250);
	Monster->SetArea((int)Water_SiX);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_SiX, Monster));

	Monster = g_pMonsterManager->GetCobolt();
	Monster->SetPosX(830);
	Monster->SetPosY(1230);
	Monster->SetArea((int)Water_Seven);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_Seven, Monster));

	Monster = g_pMonsterManager->GetCobolt();
	Monster->SetPosX(530);
	Monster->SetPosY(930);
	Monster->SetArea((int)Water_Eight);
	Monster->SetTerrain(BackGround_Magenta);
	map_Monster.insert(make_pair(Water_Eight, Monster));

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
		if (map_Monster.size() < 8)
		{
			if (map_Monster.find(Water_One) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetBee();
				Monster->SetPosX(830);
				Monster->SetPosY(340);
				Monster->SetArea((int)Water_One);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_One, Monster));
			}
			if (map_Monster.find(Water_Two) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetBee();
				Monster->SetPosX(840);
				Monster->SetPosY(670);
				Monster->SetArea((int)Water_Two);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_Two, Monster));
			}
			if (map_Monster.find(Water_Three) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetBee();
				Monster->SetPosX(880);
				Monster->SetPosY(1020);
				Monster->SetArea((int)Water_Three);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_Three, Monster));
			}
			if (map_Monster.find(Water_Four) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetBee();
				Monster->SetPosX(230);
				Monster->SetPosY(420);
				Monster->SetArea((int)Water_Four);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_Four, Monster));
			}
			if (map_Monster.find(Water_Five) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetBee();
				Monster->SetPosX(400);
				Monster->SetPosY(1285);
				Monster->SetArea((int)Water_Five);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_Five, Monster));
			}
			if (map_Monster.find(Water_SiX) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetCobolt();
				Monster->SetPosX(190);
				Monster->SetPosY(1250);
				Monster->SetArea((int)Water_SiX);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_SiX, Monster));
			}
			if (map_Monster.find(Water_Seven) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetCobolt();
				Monster->SetPosX(830);
				Monster->SetPosY(1230);
				Monster->SetArea((int)Water_Seven);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_Seven, Monster));
			}
			if (map_Monster.find(Water_Eight) == map_Monster.end())
			{
				Monster = g_pMonsterManager->GetCobolt();
				Monster->SetPosX(530);
				Monster->SetPosY(930);
				Monster->SetArea((int)Water_Eight);
				Monster->SetTerrain(BackGround_Magenta);
				map_Monster.insert(make_pair(Water_Eight, Monster));
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
				Player->SetPosX(Player->GetPosX() + ((at.right - at.left) + 5));
				break;
			case RIGHT:
				Player->SetPosX(Player->GetPosX() - ((at.right - at.left) + 5));
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

			//공격모션을 취해라 혹은 추적해라 근거리
			if (iter->second->GetType() == (MonsterType)0)
			{
				// 실질적 공격로직
				if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetLProve().x, iter->second->GetLProve().y, 15, 30)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
				{
					Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
					Player->SetisDivain(true);
					Player->SetIsHit(true);
					Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
					Player->SetPlayerDir((PlayerDir)1);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetRProve().x, iter->second->GetRProve().y, 15, 30)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
				{
					Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
					Player->SetisDivain(true);
					Player->SetIsHit(true);
					Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
					Player->SetPlayerDir((PlayerDir)0);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetTProve().x, iter->second->GetTProve().y, 30, 15)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
				{
					Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
					Player->SetisDivain(true);
					Player->SetIsHit(true);
					Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
					Player->SetPlayerDir((PlayerDir)3);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetBProve().x, iter->second->GetBProve().y, 30, 15)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
				{
					Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
					Player->SetisDivain(true);
					Player->SetIsHit(true);
					Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
					Player->SetPlayerDir((PlayerDir)2);
				}

				if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetLProve().x, iter->second->GetLProve().y, 15, 30)) && !iter->second->GetIsAttackMode())
				{
					iter->second->SetDir(MON_LEFT);
					iter->second->SetFrameX(0);
					iter->second->SetIsAttacking(true);
					iter->second->SetIsAttackMode(true);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetRProve().x, iter->second->GetRProve().y, 15, 30)) && !iter->second->GetIsAttackMode())
				{
					iter->second->SetDir(MON_RIGHT);
					iter->second->SetFrameX(0);
					iter->second->SetIsAttacking(true);
					iter->second->SetIsAttackMode(true);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetTProve().x, iter->second->GetTProve().y, 30, 15)) && !iter->second->GetIsAttackMode())
				{
					iter->second->SetDir(MON_UP);
					iter->second->SetFrameX(0);
					iter->second->SetIsAttacking(true);
					iter->second->SetIsAttackMode(true);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
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
			// 원거리
			else if (iter->second->GetType() == (MonsterType)1)
			{
				//실질적 공격
				if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetLProve().x-40, iter->second->GetLProve().y, 15, 90)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
				{
					Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
					Player->SetisDivain(true);
					Player->SetIsHit(true);
					Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
					Player->SetPlayerDir((PlayerDir)1);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetRProve().x + 40, iter->second->GetRProve().y, 15, 90)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
				{
					Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
					Player->SetisDivain(true);
					Player->SetIsHit(true);
					Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
					Player->SetPlayerDir((PlayerDir)0);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetTProve().x, iter->second->GetTProve().y -40, 90, 15)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
				{
					Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
					Player->SetisDivain(true);
					Player->SetIsHit(true);
					Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
					Player->SetPlayerDir((PlayerDir)3);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetBProve().x, iter->second->GetBProve().y + 40, 90, 15)) && iter->second->GetIsShowAttackRect() && !Player->GetIsDivain())
				{
					Player->SetHp(Player->GetHP() - iter->second->GetATK() + Player->GetDEF());
					Player->SetisDivain(true);
					Player->SetIsHit(true);
					Player->SetDamageBuffer(iter->second->GetATK() + Player->GetDEF());
					Player->SetPlayerDir((PlayerDir)2);
				}


				if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetPosX() + iter->second->GetMonsterImage()->GetFrameWidth() / 2, iter->second->GetPosY() + iter->second->GetMonsterImage()->GetFrameHeight() / 2, 90, 90)) && !iter->second->GetIsAttackMode())
				{
					if (Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight()/2 >= iter->second->GetPosY()
						&& Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 <= iter->second->GetPosY() + iter->second->GetMonsterImage()->GetFrameHeight()
						&& Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth()/2 < iter->second->GetPosX() + iter->second->GetMonsterImage()->GetFrameWidth()/2)
					{
						if(!g_pPixelManager->CheckPixel(BackGround_Magenta,iter->second->GetRProve().x,iter->second->GetRProve().y))
							iter->second->SetPosX(iter->second->GetPosX() + 1);
					}
					else if (Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 >= iter->second->GetPosY()
						&& Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 <= iter->second->GetPosY() + iter->second->GetMonsterImage()->GetFrameHeight()
						&& Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2 > iter->second->GetPosX() + iter->second->GetMonsterImage()->GetFrameWidth() / 2)
					{
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetLProve().x, iter->second->GetLProve().y))
							iter->second->SetPosX(iter->second->GetPosX() - 1);
					}
					else if (Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2 >= iter->second->GetPosX()
						&& Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2 <= iter->second->GetPosX() + iter->second->GetMonsterImage()->GetFrameWidth()
						&& Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 < iter->second->GetPosY() + iter->second->GetMonsterImage()->GetFrameHeight() / 2)
					{
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetTProve().x, iter->second->GetTProve().y))
							iter->second->SetPosY(iter->second->GetPosY() + 1);
					}
					else if (Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2 >= iter->second->GetPosX()
						&& Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2 <= iter->second->GetPosX() + iter->second->GetMonsterImage()->GetFrameWidth()
						&& Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 > iter->second->GetPosY() + iter->second->GetMonsterImage()->GetFrameHeight() / 2)
					{
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetBProve().x, iter->second->GetBProve().y))
							iter->second->SetPosY(iter->second->GetPosY() - 1);
					}
					else if (Player->GetPosX() < iter->second->GetPosX() && Player->GetPosY() < iter->second->GetPosY())
					{
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetRProve().x, iter->second->GetRProve().y))
							iter->second->SetPosX(iter->second->GetPosX() + 1);
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetTProve().x, iter->second->GetTProve().y))
							iter->second->SetPosY(iter->second->GetPosY() + 1);
					}
					else if (Player->GetPosX() < iter->second->GetPosX() && Player->GetPosY() > iter->second->GetPosY())
					{
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetRProve().x, iter->second->GetRProve().y))
							iter->second->SetPosX(iter->second->GetPosX() + 1);
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetBProve().x, iter->second->GetBProve().y))
							iter->second->SetPosY(iter->second->GetPosY() - 1);
					}
					else if (Player->GetPosX() > iter->second->GetPosX() && Player->GetPosY() < iter->second->GetPosY())
					{
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetLProve().x, iter->second->GetLProve().y))
							iter->second->SetPosX(iter->second->GetPosX() - 1);
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetTProve().x, iter->second->GetTProve().y))
							iter->second->SetPosY(iter->second->GetPosY() + 1);
					}
					else if (Player->GetPosX() > iter->second->GetPosX() && Player->GetPosY() > iter->second->GetPosY())
					{
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetLProve().x, iter->second->GetLProve().y))
							iter->second->SetPosX(iter->second->GetPosX() - 1);
						if (!g_pPixelManager->CheckPixel(BackGround_Magenta, iter->second->GetBProve().x, iter->second->GetBProve().y))
							iter->second->SetPosY(iter->second->GetPosY() - 1);
					}
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetLProve().x - 40, iter->second->GetLProve().y, 15, 90)) && !iter->second->GetIsAttackMode())
				{
					iter->second->SetDir(MON_LEFT);
					iter->second->SetFrameX(0);
					iter->second->SetIsAttacking(true);
					iter->second->SetIsAttackMode(true);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetRProve().x + 40, iter->second->GetRProve().y, 15, 90)) && !iter->second->GetIsAttackMode())
				{
					iter->second->SetDir(MON_RIGHT);
					iter->second->SetFrameX(0);
					iter->second->SetIsAttacking(true);
					iter->second->SetIsAttackMode(true);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetTProve().x, iter->second->GetTProve().y - 40, 90, 15)) && !iter->second->GetIsAttackMode())
				{
					iter->second->SetDir(MON_UP);
					iter->second->SetFrameX(0);
					iter->second->SetIsAttacking(true);
					iter->second->SetIsAttackMode(true);
				}
				else if (IntersectRect(&at,
					&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2, Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2, 20, 20),
					&RectMakeCenter(iter->second->GetBProve().x, iter->second->GetBProve().y + 40, 90, 15)) && !iter->second->GetIsAttackMode())
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
				g_pSoundManager->Play("HitSound");
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
		Place["Place"]["NAME"] = "WATER";
		ofstream Input_Place;
		Input_Place.open("PlayerPlace.json");
		Input_Place << Place;
		Input_Place.close();

		g_pSceneManager->SetNextScene(SLIST_BOSSMAP);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	else if (IntersectRect(&qt,
		&RectMakeCenter(Player->GetPosX() + Player->GetPlayerImage()->GetFrameWidth() / 2,
			Player->GetPosY() + Player->GetPlayerImage()->GetFrameHeight() / 2 + 10, 10, 10),
		&RectMake(810, 0, 40, 30)))
	{
		Place["Place"]["NAME"] = "WATER";
		ofstream Input_Place;
		Input_Place.open("PlayerPlace.json");
		Input_Place << Place;
		Input_Place.close();

		g_pSceneManager->SetNextScene(SLIST_PLAY);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}

	if (g_pKeyManager->isStayKeyDown(VK_ESCAPE))
	{
		Place["Place"]["NAME"] = "";
		ofstream Input_Place;
		Input_Place.open("PlayerPlace.json");
		Input_Place << Place;
		Input_Place.close();
		g_pSceneManager->SetNextScene(SLIST_TITLE);
		g_pSceneManager->ChangeScene(SLIST_LOADING);
	}
	if (Player->GetHP() <= 0)
	{
		Place["Place"]["NAME"] = "";
		ofstream Input_Place;
		Input_Place.open("PlayerPlace.json");
		Input_Place << Place;
		Input_Place.close();
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
//	RectangleMake(EmptyBuffer->GetMemDC(), 670, 1650, 30, 20);
	//RectangleMake(EmptyBuffer->GetMemDC(), 810, 0, 40, 30);
	EmptyBuffer->ViewPortRender(g_hDC, ViewPort, WINSIZEX, WINSIZEY);
}

void cWaterPathScene::Release()
{
	m_vMonster.clear();
}
