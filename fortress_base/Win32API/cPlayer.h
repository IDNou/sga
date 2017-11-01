#pragma once

class cProgressBar;
class cMap;
class cObjects;

#define MAP1_Y (WINSIZEY - 110)

class cPlayer
{
private:
	cImage*			m_pMapImg;			// 배경 정보 이미지

	cMap*			m_pMap;
	cObjects*		m_pObject;

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void MiniRender();
	void Render();

#pragma region Get
	
#pragma endregion

#pragma region Set
	void SetMap(cMap* map) { m_pMap = map; }
	void SetObject(cObjects * object) { m_pObject = object; }
#pragma endregion
};

