#include "CVMap.h"
#include "CVGame.h"
CVMap::CVMap(CVGame * cvGame) : Group(cvGame)
{
	this->add = cvGame->add;
}

CVMap::~CVMap()
{
}

void CVMap::BuildMap(const char * jsonChar)
{
	Json state(jsonChar);
	for (auto& it : state["groupList"].GetArray())
	{
		std::string type = it["type"].GetString();
		auto v = Json::GetCharArrayFromValue(it);
		const char* value = v.c_str();
		if (type == "TileMap") {
		
			this->tileMapGroup = this->add->TileMap(value,this);
			continue;
		}
		if (type == "QuadTree") {
			this->quadTreeGroup = new QuadTree(this->game);
			this->quadTreeGroup->SetParentObject(this);
			this->quadTreeGroup->BuildTree(value);
			continue;
		}
		if (type == "Group") {
			continue;
		}
	}
}

void CVMap::Draw()
{
	this->tileMapGroup->Draw();
	this->quadTreeGroup->Draw();
}

void CVMap::Update()
{
	this->quadTreeGroup->Update();
}

void CVMap::UpdatePhysics()
{
}
