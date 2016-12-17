#include "CVMap.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "InfoPanel.h"
#include "Simon.h"
#include "WeaponWhip.h"
#include "SimonGroup.h"
#include "CVStage.h"
#include "CVBlock.h"
CVMap::CVMap(CVGame * cvGame) : Group(cvGame)
{
	this->cvGame = cvGame;
	this->add = cvGame->add;
	this->cvAdd = cvGame->cvAdd;
	this->camera = cvGame->camera;
}

CVMap::~CVMap()
{
	delete this->tileMapGroup;
	delete this->quadTreeGroup;
	delete this->cameraActiveGroup;
	for (auto stage : this->stageList) {
		delete stage;
	}
}

void CVMap::BuildMap(const char * jsonChar)
{
	Json state(jsonChar);

	for (auto& stageJson : state["stageList"].GetArray()) 
	{
		CVStage* stage = new CVStage(Json::GetCharArrayFromValue(stageJson));
		this->stageList.push_back(stage);
	}

	this->simonGroup = this->cvAdd->AddSimonGroup();
	this->AddGroup(this->simonGroup);

	/*simon->SetParentObject(this->simonGroup);
	simon->UpdateWorldPosition();
	if (simon->body != nullptr) {
		simon->body->rigidBody->Transform(simon->worldPosition);
	}
	this->simonGroup->AddDrawObjectToList(simon);*/

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
			
			/*for (auto& obj : it["itemList"].GetArray()) {
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
			}*/
			continue;
		}
	}

	
	this->camera->FollowX(this->simon);
}
void CVMap::Update()
{
	this->quadTreeGroup->Update();
	this->cameraActiveGroup->Update();
	this->simonGroup->Update();
	this->simon->Update();
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
	//this->quadTreeGroup->UpdatePhysics();
	this->cameraActiveGroup->CheckCollisionTo(this->quadTreeGroup->GetDrawList());
	this->cameraActiveGroup->UpdatePhysics();
	this->simonGroup->CheckCollisionTo(this->quadTreeGroup->GetDrawList());
	//this->simon->body->AddListCheckCollisionTo(this->quadTreeGroup->GetDrawList());
	//this->simon->weaponWhip->body->AddListCheckCollisionTo(this->quadTreeGroup->GetDrawList());
	this->simonGroup->UpdatePhysics();
}

void CVMap::LoadSimon(InfoPanel * infoPanel, GameOverScreen *goScreen, Simon * simon)
{

	this->simon = simon;	
	this->simon->infoPanel = infoPanel;
	this->simon->goScreen = goScreen;
	this->simon->SetParentObject(this->simonGroup);
	this->simonGroup->AddDrawObjectToList(this->simon);

	this->simon->UpdateWorldPosition();

	if (simon->weaponWhip != nullptr) {
		simon->weaponWhip->SetParentObject(this->simonGroup);
		this->simonGroup->AddDrawObjectToList(simon->weaponWhip);
		simon->weaponWhip->SetTransformBasedOn(this->simon);
	}

	this->camera->SetPoint(this->simon->worldPosition);
	this->camera->FollowX(this->simon);
	this->simon->SetGroupToCheckCollision(cameraActiveGroup);
}
