#include "CVMap.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "InfoPanel.h"
CVMap::CVMap(CVGame * cvGame) : Group(cvGame)
{
	this->cvGame = cvGame;
	this->add = cvGame->add;
	this->cvAdd = cvGame->cvAdd;
}

CVMap::~CVMap()
{
	delete this->tileMapGroup;
	delete this->quadTreeGroup;
	delete this->movingGroup;
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

	this->simonGroup = this->add->Group();
	this->AddGroup(this->simonGroup);
}
void CVMap::Update()
{
	this->quadTreeGroup->Update();
	this->simonGroup->Update();
}
void CVMap::Draw()
{
	this->tileMapGroup->Draw();
	this->quadTreeGroup->Draw();
	this->simonGroup->Draw();
	auto drawList = this->quadTreeGroup->GetDrawList();
	for (auto it = drawList.begin(); it != drawList.end(); ++it) {
		(*it)->body->Render();
	}
}



void CVMap::UpdatePhysics()
{
	this->quadTreeGroup->UpdatePhysics();
	this->simonGroup->UpdatePhysics();
}

void CVMap::LoadSimon(InfoPanel * infoPanel, Simon * simon)
{

	if (simon == nullptr) {
		this->simon = this->cvAdd->CharSimon(100, GAME_HEIGHT - 50, 16, infoPanel, simonGroup);
		this->cvGame->simon = this->simon;
	}
	else {
		this->simon = simon;
		this->simon->SetParentObject(this->simonGroup);
		this->simonGroup->AddDrawObjectToList(simon);
	}
}
