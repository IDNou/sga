#pragma once

class cProgressBar;
class cMap;
class cObject;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cMap*			m_pMap;
	cObject*		m_pObject;

	bool			isSame;
	bool			isCreate;
	bool			isExist;
	bool			isMove;
	int				count;
	

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();

	bool GetIsCreate() { return isCreate; }

	void SetMap(cMap* map) { m_pMap = map; }
	void SetObject(cObject* object) { m_pObject = object; }
	void SetIsCreate(bool create) { isCreate = create; }

};

