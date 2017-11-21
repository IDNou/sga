#pragma once

class cProgressBar;
class c2048Map;
class c2048Object;

#define MAP1_Y (WINSIZEY - 110)

class c2048Player
{
private:
	c2048Map*			m_pMap;
	c2048Object*		m_pObject;

	bool			isCreate;
	bool			isExist;
	bool			isNotExist;
	int				iterCount;
	int				lastCount;
	int				SumCount;
	int				SumCount2;


public:
	c2048Player();
	~c2048Player();

	void Setup();
	void Update();
	void Render();

	bool GetIsCreate() { return isCreate; }

	void SetMap(c2048Map* map) { m_pMap = map; }
	void SetObject(c2048Object* object) { m_pObject = object; }
	void SetIsCreate(bool create) { isCreate = create; }

};

