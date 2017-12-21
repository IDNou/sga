#include "stdafx.h"
#include "cItemManager.h"


cItemManager::cItemManager()
{
}


cItemManager::~cItemManager()
{
}

void cItemManager::Start()
{
	ifstream File_Item;
	File_Item.open("ItemList.json");
	File_Item >> ItemList;
	File_Item.close();

	json ImageList;
	ifstream File_Image;
	File_Image.open("ImageList.json");
	File_Image >> ImageList;
	File_Image.close();

	//아이템 이미지 추가
	for (int j = 0; j < ImageList["Image"].size(); j++)
	{
		string RouteName = ImageList["Image"][j]["ROUTE"];

		g_pImageManager->AddImage(ImageList["Image"][j]["NAME"],
			RouteName.c_str(),
			ImageList["Image"][j]["WIDTH"],
			ImageList["Image"][j]["HEIGHT"],
			true,
			RGB(255, 0, 255));
	}

	//아이템 추가
	for (int i = 0; i < ItemList["Item"].size(); i++)
	{
		g_pItemManager->ItemAdd(ItemList["Item"][i]["NAME"],
			g_pImageManager->FindImage(ItemList["Item"][i]["NAME"]),
			(ItemType)ItemList["Item"][i]["TYPE"],
			ItemList["Item"][i]["ATK"],
			ItemList["Item"][i]["DEF"],
			ItemList["Item"][i]["HP"],
			ItemList["Item"][i]["PRICE"]);
	}
}

void cItemManager::Update()
{
}

void cItemManager::Render()
{
}

cItem * cItemManager::ItemAdd(string key, cImage * img, ItemType type, int ATK, int DEF, int HP, int Price)
{

	// 추가 하려는 키 값에 해당하는 이미지가 존재하는지 확인
	cItem* item = FindItem(key);

	// 추가 하려는 이미지가 이미 존재한다면 새로 만들지 않고 반환
	// 그렇지 않은 경우 새로 추가하고 추가 된 녀석을 반환
	if (item == NULL)
	{
		item = new cItem;
		item->SetupItem(key, img, type, ATK, DEF, HP, Price);
		//m_mapImage.insert(pair<string, cImage*>(key, img));
		m_mapItem.insert(make_pair(key, item));
	}

	return item;
}

cItem * cItemManager::FindItem(string key)
{
	// 맵에서 키 값에 해당하는 자료를 찾아서 이터레이터에 넣는다.
	m_mapIter = m_mapItem.find(key);

	// 키 값에 해당하는 데이터가 있는 경우 데이터 값을 반환
	// first == 키 값, second == 데이터 값
	if (m_mapIter != m_mapItem.end())
		return m_mapIter->second;

	// 키 값에 해당하는 데이터가 없는 경우 널 반환
	return NULL;
}

void cItemManager::ItemRelease(string key)
{
	m_mapIter = m_mapItem.find(key);

	if (m_mapIter != m_mapItem.end())
	{
		// 이미지 해제
		//if (m_mapIter->second != NULL)
		//	delete m_mapIter->second;

		// 매크로 사용 위와 동일한 의미
		SAFE_DELETE(m_mapIter->second);

		// 맵에서 해당 키 자료 삭제(맵에서만 빠짐)
		m_mapItem.erase(m_mapIter);
	}
}
