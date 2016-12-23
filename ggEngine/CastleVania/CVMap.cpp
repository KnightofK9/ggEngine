#include "CVMap.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "InfoPanel.h"
#include "Simon.h"
#include "WeaponWhip.h"
#include "SimonGroup.h"
#include "CVStage.h"
#include "CVBlock.h"
#include "Constant.h"
#include "CVCamera.h"
#include "EnemyGroup.h"
#include "StaticTIleManager.h"
#include "EnemyManager.h"
CVMap::CVMap(CVGame * cvGame) : Group(cvGame)
{
	this->cvGame = cvGame;
	this->add = cvGame->add;
	this->cvAdd = cvGame->cvAdd;
	this->camera = dynamic_cast<CVCamera*>(cvGame->camera);
}

CVMap::~CVMap()
{
	delete this->tileMapGroup;
	delete this->quadTreeGroup;
	delete this->simonGroup;
	delete this->projectileGroup;
	//delete this->cameraActiveGroup;
	for (auto stage : this->stageList) {
		delete stage;
	}
}

void CVMap::BuildMap(const char * jsonChar, int level)
{
	this->levelNumber = level;
	Json state(jsonChar);

	for (auto& stageJson : state["stageList"].GetArray()) 
	{
		CVStage* stage = new CVStage(Json::GetCharArrayFromValue(stageJson));
		this->stageList.push_back(stage);
	}

	this->quadTreeGroup = new QuadTree(this->game); //The background tile
	this->quadTreeGroup->SetParentObject(this);
	
	this->enemyGroup = new EnemyGroup(this->cvGame); //The enemy group
	this->enemyGroup->SetParentObject(this);
	
	this->projectileGroup = new Group(this->cvGame); //The projectile group, where all simon sub weapon and enemy skill in
	this->projectileGroup->SetParentObject(this);
	
	this->simonGroup = this->cvAdd->AddSimonGroup(); //The simon group
	this->simonGroup->SetParentObject(this);


	//
	//Collision logic
	//
	this->enemyGroup->AddGroupToCheckCollision(this->quadTreeGroup);

	this->simonGroup->AddGroupToCheckCollision(this->quadTreeGroup);
	this->simonGroup->AddGroupToCheckCollision(this->enemyGroup);

	this->projectileGroup->AddGroupToCheckCollision(this->quadTreeGroup);
	this->projectileGroup->AddGroupToCheckCollision(this->enemyGroup);
	this->projectileGroup->AddGroupToCheckCollision(this->simonGroup);

	//cameraActiveGroup = new CameraActiveGroup(this->cvGame);
	//this->cameraActiveGroup->SetParentObject(this);

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
			this->quadTreeGroup->BuildTree(value);
			this->quadTreeGroup->SetTopModifier(Constant::UI_INFO_PANEL_BACKGROUND_HEIGHT / (this->camera->GetScale().y));
			continue;
		}
		if (type == "CameraActiveGroup") {
			for (auto & obj : it["itemList"].GetArray()) {
				GameObject* go = game->GetObjectInstance(Json::GetCharArrayFromValue(obj).c_str(), enemyGroup);
				if (go != nullptr) {
					go->UpdateWorldPosition();
					if (go->body != nullptr) go->body->PreUpdate();
					/*enemyGroup->AddDrawObjectToList(go);
					go->UpdateWorldPosition();
					auto enemy = dynamic_cast<EnemyBase*>(go);
					if (enemy != nullptr) {
						enemy->Active();
					}*/
				}
				else {
					std::string type = obj["type"].GetString();
					g_debug.Log("Type not found!" + type);
				}
			}

			continue;
		}
		if (type == "Simon") {
			continue;
		}
	}

}
void CVMap::Update()
{
	this->quadTreeGroup->Update();
	//this->cameraActiveGroup->Update();
	this->enemyGroup->Update();
	this->simonGroup->Update();
	this->projectileGroup->Update();
	this->simon->Update();

}
void CVMap::Draw()
{
	this->tileMapGroup->Draw();
	this->quadTreeGroup->Draw();
	//this->cameraActiveGroup->Draw();
	this->enemyGroup->Draw();
	this->simonGroup->Draw();
	this->projectileGroup->Draw();
	auto bodyList = this->simonGroup->GetBodyList();
	for (auto body : bodyList) {
		body->Render();
	}
	auto drawList = this->quadTreeGroup->GetDrawList();
	for (auto it = drawList.begin(); it != drawList.end(); ++it) {
		(*it)->body->Render();
	}
	drawList = enemyGroup->GetDrawList();
	for (auto it = drawList.begin(); it != drawList.end(); ++it) {
		if((*it)->body!=nullptr && (*it)->body->IsActive() && (*it)->body->IsEnable())(*it)->body->Render();
	}
	CheckIfSimonOutOfBlock();
}



void CVMap::UpdatePhysics()
{
	//this->quadTreeGroup->UpdatePhysics();
	//this->cameraActiveGroup->CheckCollisionTo(this->quadTreeGroup->GetDrawList());
	//this->cameraActiveGroup->UpdatePhysics();

	//this->enemyGroup->CheckCollisionTo(this->quadTreeGroup->GetDrawList());
	this->enemyGroup->UpdatePhysics();

	this->projectileGroup->UpdatePhysics();
	//this->simonGroup->CheckCollisionTo(this->quadTreeGroup->GetDrawList());
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
	this->simon->currentMap = this;

	if (simon->weaponWhip != nullptr) {
		simon->weaponWhip->SetParentObject(this->simonGroup);
		this->simonGroup->AddDrawObjectToList(simon->weaponWhip);
		simon->weaponWhip->SetTransformBasedOn(this->simon);
	}
	this->infoPanel = infoPanel;
	this->simonGroup->AddDrawObjectToList(this->infoPanel);
	//this->simon->body->ResetGroupCheckCollisionTo();
	//this->simon->body->AddGroupCheckCollisionTo(enemyGroup);
	this->simon->body->allowWorldBlock = false;
	this->simon->body->allowWorldBound = false;
	this->simon->body->allowWorldBounciness = false;
	SetStage(0, 0, true);
}

void CVMap::SetStage(int stageNumber, int blockNumber,bool isRestartState)
{
	this->currentStage = this->stageList[stageNumber];
	SetBlock(blockNumber, isRestartState);
}

void CVMap::SetBlock(int blockNumber,bool isRestartState)
{
	this->currentBlock = this->currentStage->blockList[blockNumber];
	if (isRestartState && blockNumber == 0) {
		this->simon->ResetState();
		this->simon->position = this->currentBlock->simonSpawnPosition;
	}
	else {
		if (blockNumber == 0 && door != nullptr) {
			StartSwitchingState();
			return;
		}
		if (this->simon->currentLadderTween != nullptr) {
			this->simon->currentLadderTween->CallFinish()->Stop();
			this->simon->currentLadderTween = nullptr;
			/*this->simon->currentLadderTween->SetOnFinish([this]() {
				this->SetSimonPositionOnChangeBlock();
				this->simon->currentLadderTween = nullptr;
			});*/
		}
		if(simon->isClimbingLadder) this->SetSimonPositionOnChangeBlock();
		/*switch (this->levelNumber) {
		case -1:
			switch (blockNumber) {
			case 0:
				this->simon->position.x += 32;
				this->simon->position.y += 16;
				break;
			case 1:
				this->simon->position.x -= 32;
				this->simon->position.y -= 16;
				break;
			}

			break;
		case 2:
			break;
		case 3:
			break;
		}*/
	}
	this->simon->body->PreUpdate();

	this->camera->SetBlock(this->currentBlock);
	//this->camera->SetPoint(this->currentBlock->cameraSpawnPosition);
	this->camera->Follow(this->simon);


}

void CVMap::OnOutOfBlock(Rect r)
{
	int nextBlock = -1;
	if(r.top == -1) r = this->simon->body->GetRect();
	int nextStage = this->currentStage->stageIndex;
	for (auto stage : this->stageList) {
		for (auto block : stage->blockList) {
			Rect i;
			if (Rect::intersect(i, r, (*block))) {
				nextBlock = block->blockIndex;
				nextStage = stage->stageIndex;
				break;
			}
		}
		if (nextBlock != -1) break;
	}
	if (nextBlock == -1) {
		OnFallOutOfMap();
		return;
	}
	
	if (nextStage == this->stageList.size()) {
		OnNextLevel(++this->levelNumber);
		return;
	}
	if (this->currentStage->stageIndex != nextStage) {
		OnNextStage(nextStage,nextBlock);
		return;
	}
	this->OnNextBlock(nextBlock);
}

void CVMap::OnNextLevel(int levelIndex)
{
	g_debug.Log("On Next Level" + std::to_string(levelIndex));
	if (levelIndex == 0) {
		SetStage(0, 0);
	}
}

void CVMap::OnNextBlock(int blockIndex)
{
	g_debug.Log("On Next Block" + std::to_string(blockIndex));
	SetBlock(blockIndex);
}

void CVMap::OnNextStage(int stageIndex, int blockIndex)
{
	g_debug.Log("On Next Stage" + std::to_string(stageIndex) +" at block "+ std::to_string(blockIndex));
	SetStage(stageIndex, blockIndex,false);
}

void CVMap::OnFallOutOfMap()
{
}

void CVMap::OnEnterDoor(Door *door)
{
	Rect r = this->simon->body->GetRect();
	Vector translate = (door->worldPosition - this->simon->worldPosition) * 10;
	bool isLeft = this->simon->isLeft;
	//r.top += translate.x;
	r.left += translate.x;
	r.right += translate.x;
	//r.bottom += translate.x;
	door->OpenDoor(isLeft);
	this->door = door;
	OnOutOfBlock(r);
}

void CVMap::CheckIfSimonOutOfBlock()
{
	if (isSwitchingStage) return;
	if (!simon->isClimbingLadder) return;
	Rect r = simon->body->GetRect();
	Rect i;
	if (!Rect::intersect(i, r, (*currentBlock))) {
		OnOutOfBlock();
	}

}

void CVMap::StartSwitchingState()
{
	this->isSwitchingStage = true;
	this->door->body->SetEnable(false);
	Vector moveToPosition = this->currentBlock->simonSpawnPosition;
	Vector point = moveToPosition;
	Rect r(point.x - this->camera->GetWidth() / 2, point.y - this->camera->GetHeight() / 2,
		point.x + this->camera->GetWidth() / 2, point.y + this->camera->GetHeight() / 2);
	auto block = this->currentBlock;
	double blockTop = block->top - floor(Constant::UI_INFO_PANEL_BACKGROUND_HEIGHT / this->scale.y);
	if (r.left < block->left)
		point.x += block->left - r.left;
	if (r.right > block->right)
		point.x -= r.right - block->right;
	if (r.top < blockTop)
		point.y += blockTop - r.top;
	if (r.bottom > block->bottom)
		point.y -= r.bottom - block->bottom;

	this->simon->ResetState();
	this->simon->PlayAnimation("move");
	this->simon->body->velocity = Vector::Zero();

	this->simon->allowControl = false;
	this->simon->body->allowGravity = true;
	this->simon->body->immoveable = false;
	this->camera->SetBlock(nullptr);
	this->camera->UnFollow();



	this->add->Tween(this->camera->point.x, point.x, 3000)->SetOnFinish([this]() {
		this->isSwitchingStage = false;
		this->simon->allowControl = true;
		this->simon->body->immoveable = false;
		this->door->body->SetEnable(true);
		this->simon->body->allowGravity = true;
		this->door = nullptr;
		this->camera->Follow(this->simon);
		this->camera->SetBlock(this->currentBlock);
	})->Start();

	Vector moveFrom = this->simon->position;
	int modifier = 1;
	if (simon->isLeft) modifier = -1;
	this->simon->body->acceleration = Vector::Zero();
	double distance = abs(moveToPosition.x - this->simon->position.x)*DEFAULT_MS_PER_FRAME_FOR_ANIMATION;
	double time = 2000;
	this->simon->body->velocity.x = modifier*distance/time;
	/*this->add->Tween(this->simon->position.x, moveToPosition.x, 2000)->SetOnFinish([this]() {
		this->simon->PlayAnimation("idle");
	})->Start();*/
	this->simon->isSwitchingState = true;
	this->add->TimeOut(time, [this]() {
		this->simon->isSwitchingState = false;
		this->simon->body->velocity.x = 0;
		this->simon->PlayAnimation("idle");
	})->Start();
}

void CVMap::SetSimonPositionOnChangeBlock()
{
	if (this->simon->isLeft) {
		this->simon->position.x += 16;
	}
	else {
		this->simon->position.x -= 16;
	}

	if (this->simon->isClimbingUp) {
		//ERROR
		this->simon->position.y -= 16;
	}
	else {
		this->simon->position.y += 16;
	}
}

