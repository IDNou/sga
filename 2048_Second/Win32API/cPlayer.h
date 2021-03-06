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

	bool			isCreate;
	bool			isExist;
	bool			isNotExist;
	int				iterCount;
	int				lastCount;
	int				SumCount;
	int				SumCount2;
	

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

