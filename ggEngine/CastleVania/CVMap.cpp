#include "CVMap.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "InfoPanel.h"
#include "Simon.h"
#include "WeaponWhip.h"
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
	delete this->cameraActiveGroup;
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
		if (type == "CameraActiveGroup") {
			cameraActiveGroup = new CameraActiveGroup(this->cvGame);
			this->cameraActiveGroup->SetParentObject(this);
			continue;
		}
		if (type == "Simon") {
			this->simonGroup = this->add->Group();
			this->AddGroup(this->simonGroup);
			for (auto& obj : it["itemList"].GetArray()) {
				std::string type = obj["type"].GetString();
				GameObject* go = game->GetObjectInstance(Json::GetCharArrayFromValue(obj).c_str());
				if (go != nullptr) {
					if (type == "Simon") {
						this->simon = dynamic_cast<Simon*>(go);
						go->SetParentObject(this->simonGroup);
						go->UpdateWorldPosition();
						if (go->body != nullptr) {
							go->body->rigidBody->Transform(go->worldPosition);
						}
						this->simonGroup->AddDrawObjectToList(go);
						this->simon->AddWhip();
						this->cvGame->simon = this->simon;
						continue;
					}
				}
				else {				
					g_debug.Log("Type not found!" + type);
				}
			}
			continue;
		}
	}

	
}
void CVMap::Update()
{
	this->quadTreeGroup->Update();
	this->cameraActiveGroup->Update();
	this->simonGroup->Update();
}
void CVMap::Draw()
{
	this->tileMapGroup->Draw();
	this->quadTreeGroup->Draw();
	this->cameraActiveGroup->Draw();
	this->simonGroup->Draw();
	auto simonList = this->simonGroup->GetDrawList();
	for (auto go : simonList) {
		go->body->Render();
	}
	auto drawList = this->quadTreeGroup->GetDrawList();
	for (auto it = drawList.begin(); it != drawList.end(); ++it) {
		(*it)->body->Render();
	}
}



void CVMap::UpdatePhysics()
{
	this->quadTreeGroup->UpdatePhysics();
	this->cameraActiveGroup->UpdatePhysics();
	this->simon->body->AddListCheckCollisionTo(this->quadTreeGroup->GetDrawList());
	this->simonGroup->UpdatePhysics();
}

void CVMap::LoadSimon(InfoPanel * infoPanel, Simon * simon)
{

	if (this->simon  == nullptr ) {
		if (simon == nullptr) {
			this->simon = this->cvAdd->CharSimon(100, GAME_HEIGHT - 50, 16, infoPanel, simonGroup);
			this->cvGame->simon = this->simon;
		}
		else {
			this->simon = simon;
		}
	}
	else {
		this->simon->infoPanel = infoPanel;
	}
}
