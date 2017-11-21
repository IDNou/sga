#pragma once

class cItemKind
{
private:
	tagItemInfo					itemInfo;
	map<string, tagItemInfo>	item;
public:
	cItemKind();
	~cItemKind();

	void Setup();
	void Update();
	void Render();
};

