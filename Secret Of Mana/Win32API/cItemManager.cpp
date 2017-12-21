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

	//������ �̹��� �߰�
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

	//������ �߰�
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

	// �߰� �Ϸ��� Ű ���� �ش��ϴ� �̹����� �����ϴ��� Ȯ��
	cItem* item = FindItem(key);

	// �߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� ��ȯ
	// �׷��� ���� ��� ���� �߰��ϰ� �߰� �� �༮�� ��ȯ
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
	// �ʿ��� Ű ���� �ش��ϴ� �ڷḦ ã�Ƽ� ���ͷ����Ϳ� �ִ´�.
	m_mapIter = m_mapItem.find(key);

	// Ű ���� �ش��ϴ� �����Ͱ� �ִ� ��� ������ ���� ��ȯ
	// first == Ű ��, second == ������ ��
	if (m_mapIter != m_mapItem.end())
		return m_mapIter->second;

	// Ű ���� �ش��ϴ� �����Ͱ� ���� ��� �� ��ȯ
	return NULL;
}

void cItemManager::ItemRelease(string key)
{
	m_mapIter = m_mapItem.find(key);

	if (m_mapIter != m_mapItem.end())
	{
		// �̹��� ����
		//if (m_mapIter->second != NULL)
		//	delete m_mapIter->second;

		// ��ũ�� ��� ���� ������ �ǹ�
		SAFE_DELETE(m_mapIter->second);

		// �ʿ��� �ش� Ű �ڷ� ����(�ʿ����� ����)
		m_mapItem.erase(m_mapIter);
	}
}
