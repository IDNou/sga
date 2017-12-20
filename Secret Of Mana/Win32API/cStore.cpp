#include "stdafx.h"
#include "cStore.h"


cStore::cStore()
{
}

cStore::~cStore()
{
}

void cStore::Setup()
{
	Player = g_pPlayerManager->GetPlayer();
	EmptyBuffer = g_pImageManager->FindImage("Store_Empty");
	CommunicationBox = g_pImageManager->FindImage("CommunicationBox");
	Finger = g_pImageManager->FindImage("Finger2");
	Finger->SetPosX(Player->GetViewPort().left + 40);
	Finger->SetPosY(Player->GetViewPort().top + 70);

	json ItemList;
	ifstream File_Item;
	File_Item.open("ItemList.json");
	File_Item >> ItemList;
	File_Item.close();

	for (int i = 0; i < ItemList["Item"].size(); i++)
		vec_Item.push_back(g_pItemManager->FindItem(ItemList["Item"][i]["NAME"]));

	InvenMagin = 70;
	StoreMagin = 70;
	count = 1;
	isSell = false;
	isNotBuy = false;
	isOwn = false;
	isConsumOwn = false;
	isWear = false;
}

void cStore::Update()
{
	InvenMagin = 70;
	StoreMagin = 70;

	cout << count  << " " << Player->GetPlayerInven().size() << endl;

	if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		isNotBuy = false;
		isOwn = false;
		isConsumOwn = false;
		isWear = false;

		// 판매
		if (isSell && Player->GetPlayerInven()[count - 1]->GetIsWear() && Player->GetPlayerInven().size() > 0)
		{
			isWear = true;
		}
		else if (isSell && !Player->GetPlayerInven()[count - 1]->GetIsWear() && Player->GetPlayerInven().size() > 0)
		{
			Player->SetMONEY(Player->GetMoney() + Player->GetPlayerInven()[count-1]->GetPrice());

			for (auto iter = Player->GetPlayerInven().begin(); iter != Player->GetPlayerInven().end(); )
			{
				if ((*iter)->GetName() == Player->GetPlayerInven()[count-1]->GetName())
				{
					iter = Player->GetPlayerInven().erase(iter);
					break;
				}
				else
					iter++;
			}
		}
		//구매
		else if(!isSell)
		{
			for (auto iter = Player->GetPlayerInven().begin(); iter != Player->GetPlayerInven().end(); iter++)
			{
				if ((*iter)->GetName() == vec_Item[count - 1]->GetName() && (*iter)->GetType() == (ItemType)1)
				{
					//아이템을 가지고있습니다.
					isOwn = true;
					break;
				}
				else if ((*iter)->GetName() == vec_Item[count - 1]->GetName() 
					&& (*iter)->GetType() == (ItemType)0 
					&& Player->GetMoney() >= vec_Item[count - 1]->GetPrice())
				{
					// 회복템을 가지고 있습니다. 돈도있구
					(*iter)->SetAmount((*iter)->GetAmount() + 1);
					Player->SetMONEY(Player->GetMoney() - vec_Item[count - 1]->GetPrice());
					isConsumOwn = true;
					break;
				}
				else if ((*iter)->GetName() == vec_Item[count - 1]->GetName() 
					&& (*iter)->GetType() == (ItemType)0 
					&& Player->GetMoney() < vec_Item[count - 1]->GetPrice())
				{
					// 회복템을 가지고 있습니다. 돈은 없구
					isNotBuy = true;
					isConsumOwn = true;
					break;
				}
			}
	
			if (!isOwn && !isConsumOwn && Player->GetMoney() >= vec_Item[count - 1]->GetPrice())
			{
				vec_Item[count - 1]->SetAmount(1);
				Player->GetPlayerInven().push_back(vec_Item[count - 1]);
				Player->SetMONEY(Player->GetMoney() - vec_Item[count - 1]->GetPrice());
			}
			else if(!isOwn && isConsumOwn && Player->GetMoney() < vec_Item[count - 1]->GetPrice())
			{
				//메세지 출력
				isNotBuy = true;
			}
			else if (!isOwn && !isConsumOwn && Player->GetMoney() < vec_Item[count - 1]->GetPrice())
			{
				isNotBuy = true;
			}
		}
	}

	if(g_pKeyManager->isOnceKeyDown(VK_LEFT))
	{ 
		if (isSell)
		{
			Finger->SetPosX(Finger->GetPosX() - 245);
			Finger->SetPosY(Player->GetViewPort().top + 70);
			count = 1;
			isSell = false;
		}
	}
	if (g_pKeyManager->isOnceKeyDown(VK_RIGHT))
	{
		if (!isSell)
		{
			Finger->SetPosX(Finger->GetPosX() + 245);
			Finger->SetPosY(Player->GetViewPort().top + 70);
			count = 1;
			isSell = true;
		}
	}
	if (g_pKeyManager->isOnceKeyDown(VK_UP))
	{
		if (count > 1)
		{
			Finger->SetPosY(Finger->GetPosY() - 20);
			count--;
		}
	}
	if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
	{
		if (isSell)
		{
			if (count < Player->GetPlayerInven().size())
			{
				Finger->SetPosY(Finger->GetPosY() + 20);
				count++;
			}
		}
		else
		{
			if (count < vec_Item.size())
			{
				Finger->SetPosY(Finger->GetPosY() + 20);
				count++;
			}
		}
	}

	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
	{
		vec_Item.clear();
	}
}

void cStore::Render(HDC hdc)
{
	char Buffer[256];
	EmptyBuffer->AlphaRender(hdc, Player->GetViewPort().left, Player->GetViewPort().top, 128);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i == 0 && j == 0)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 390 + j * 15, Player->GetViewPort().top + 10 + i * 15, 0, 0);
			else if (i == 0 && j == 7 - 1)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 390 + j * 15, Player->GetViewPort().top + 10 + i * 15, 2, 0);
			else if (i == 2 - 1 && j == 0)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 390 + j * 15, Player->GetViewPort().top + 10 + i * 15, 0, 2);
			else if (i == 2 - 1 && j == 7 - 1)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 390 + j * 15, Player->GetViewPort().top + 10 + i * 15, 2, 2);
			else if (i == 0 && (j != 0 || j != 7 - 1))
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 390 + j * 15, Player->GetViewPort().top + 10 + i * 15, 1, 0);
			else if ((i != 0 || i != 2 - 1) && j == 0)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 390 + j * 15, Player->GetViewPort().top + 10 + i * 15, 0, 1);
			else if ((i != 0 || i != 2 - 1) && j == 7 - 1)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 390 + j * 15, Player->GetViewPort().top + 10 + i * 15, 2, 1);
			else if (i == 2 - 1 && (j != 0 || j != 7 - 1))
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 390 + j * 15, Player->GetViewPort().top + 10 + i * 15, 1, 2);
		}
	}

	for (int i = 0; i < MessegeHeight; i++)
	{
		for (int j = 0; j < MessageWidth; j++)
		{
			if (i == 0 && j == 0)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 25 + j * 15, Player->GetViewPort().top + 50 + i * 15, 0, 0);
			else if (i == 0 && j == MessageWidth - 1)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 25 + j * 15, Player->GetViewPort().top + 50 + i * 15, 2, 0);
			else if (i == MessegeHeight - 1 && j == 0)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 25 + j * 15, Player->GetViewPort().top + 50 + i * 15, 0, 2);
			else if (i == MessegeHeight - 1 && j == MessageWidth - 1)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 25 + j * 15, Player->GetViewPort().top + 50 + i * 15, 2, 2);
			else if (i == 0 && (j != 0 || j != MessageWidth - 1))
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 25 + j * 15, Player->GetViewPort().top + 50 + i * 15, 1, 0);
			else if ((i != 0 || i != MessegeHeight - 1) && j == 0)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 25 + j * 15, Player->GetViewPort().top + 50 + i * 15, 0, 1);
			else if ((i != 0 || i != MessegeHeight - 1) && j == MessageWidth - 1)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 25 + j * 15, Player->GetViewPort().top + 50 + i * 15, 2, 1);
			else if (i == MessegeHeight - 1 && (j != 0 || j != MessageWidth - 1))
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 25 + j * 15, Player->GetViewPort().top + 50 + i * 15, 1, 2);
		}
	}

	for (int i = 0; i < MessegeHeight; i++)
	{
		for (int j = 0; j < MessageWidth; j++)
		{
			if (i == 0 && j == 0)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 270 + j * 15, Player->GetViewPort().top + 50 + i * 15, 0, 0);
			else if (i == 0 && j == MessageWidth - 1)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 270 + j * 15, Player->GetViewPort().top + 50 + i * 15, 2, 0);
			else if (i == MessegeHeight - 1 && j == 0)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 270 + j * 15, Player->GetViewPort().top + 50 + i * 15, 0, 2);
			else if (i == MessegeHeight - 1 && j == MessageWidth - 1)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 270 + j * 15, Player->GetViewPort().top + 50 + i * 15, 2, 2);
			else if (i == 0 && (j != 0 || j != MessageWidth - 1))
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 270 + j * 15, Player->GetViewPort().top + 50 + i * 15, 1, 0);
			else if ((i != 0 || i != MessegeHeight - 1) && j == 0)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 270 + j * 15, Player->GetViewPort().top + 50 + i * 15, 0, 1);
			else if ((i != 0 || i != MessegeHeight - 1) && j == MessageWidth - 1)
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 270 + j * 15, Player->GetViewPort().top + 50 + i * 15, 2, 1);
			else if (i == MessegeHeight - 1 && (j != 0 || j != MessageWidth - 1))
				CommunicationBox->FrameRender(hdc, Player->GetViewPort().left + 270 + j * 15, Player->GetViewPort().top + 50 + i * 15, 1, 2);
		}
	}

	sprintf_s(Buffer, "%d 루크", Player->GetMoney());
	//SetBkColor(hdc, SRCCOPY);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, Player->GetViewPort().left+ 420, Player->GetViewPort().top+17, Buffer, strlen(Buffer));

	Finger->Render(hdc, Finger->GetPosX(), Finger->GetPosY());

	for (auto iter = vec_Item.begin(); iter != vec_Item.end(); iter++)
	{
		(*iter)->GetImage()->Render(hdc, Player->GetViewPort().left + 60, Player->GetViewPort().top + StoreMagin);
		sprintf_s(Buffer, "%d 루크", (*iter)->GetPrice());
		TextOut(hdc, Player->GetViewPort().left + 100, Player->GetViewPort().top + StoreMagin, Buffer, strlen(Buffer));
		StoreMagin += 20;
	}

	for (auto iter = Player->GetPlayerInven().begin(); iter != Player->GetPlayerInven().end(); iter++)
	{
		(*iter)->GetImage()->Render(hdc, Player->GetViewPort().left + 305, Player->GetViewPort().top + InvenMagin);
		sprintf_s(Buffer, "%d 루크", (*iter)->GetPrice());
		TextOut(hdc, Player->GetViewPort().left + 345, Player->GetViewPort().top + InvenMagin, Buffer, strlen(Buffer));
		sprintf_s(Buffer, "%d 개", (*iter)->GetAmount());
		TextOut(hdc, Player->GetViewPort().left + 425, Player->GetViewPort().top + InvenMagin, Buffer, strlen(Buffer));
		InvenMagin += 20;
	}

	if (isNotBuy)
	{
		SetBkMode(hdc, OPAQUE);
		TextOut(hdc, Player->GetViewPort().left + 200, Player->GetViewPort().top + 17, "돈이 부족합니다.", strlen("돈이 부족합니다."));
	}
	else if (isOwn)
	{
		SetBkMode(hdc, OPAQUE);
		TextOut(hdc, Player->GetViewPort().left + 200, Player->GetViewPort().top + 17, "이미 가지고 있습니다.", strlen("이미 가지고 있습니다."));
	}
	else if (isWear)
	{
		SetBkMode(hdc, OPAQUE);
		TextOut(hdc, Player->GetViewPort().left + 200, Player->GetViewPort().top + 17, "착용 중 입니다.", strlen("착용 중 입니다."));
	}
}
