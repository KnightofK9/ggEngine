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
#include "CVMapManager.h"
CVMap::CVMap(CVGame * cvGame) : Group(cvGame)
{
	this->cvGame = cvGame;
	this->add = cvGame->add;
	this->cvAdd = cvGame->cvAdd;
	this->camera = dynamic_cast<CVCamera*>(cvGame->camera);
#ifdef DEBUG_ENABLE_SET_STAGE_BLOCK_KEY_CONTROL
	debugStageKey[KeyControlSetStageBlock::PreviousBlock] = DIK_F1;
	debugStageKey[KeyControlSetStageBlock::NextBlock] = DIK_F2;
	debugStageKey[KeyControlSetStageBlock::PreviousStage] = DIK_F3;
	debugStageKey[KeyControlSetStageBlock::NextStage] = DIK_F4;
#endif // DEBUG_ENABLE_SET_STAGE_BLOCK_KEY_CONTROL
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

void CVMap::BuildMap(std::string name, const char * jsonChar, int level)
{
	this->name = name;
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


	for (auto& it : state["groupList"].GetArray())
	{
		std::string type = it["type"].GetString();
		auto v = Json::GetCharArrayFromValue(it);
		const char* value = v.c_str();
		if (type == "TileMap") {
		
			this->tileMapGroup = this->add->TileMap(name, value,this);
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
	this->enemyGroup->Update();
	this->simonGroup->Update();
	this->projectileGroup->Update();
	this->simon->Update();
	DebugUpdate();
	
}
void CVMap::Draw()
{
	this->tileMapGroup->Draw();
	this->quadTreeGroup->Draw();
	this->enemyGroup->Draw();
	this->simonGroup->Draw();
	this->projectileGroup->Draw();


	Physics::RenderGroupBodyList(this->quadTreeGroup);
	Physics::RenderGroupBodyList(this->enemyGroup);
	Physics::RenderGroupBodyList(this->projectileGroup);
	Physics::RenderGroupBodyList(this->simonGroup);

	//g_debug.Log("Number of projectile " + std::to_string( this->projectileGroup->GetDrawList().size()));
	CheckIfSimonOutOfBlock();
}



void CVMap::UpdatePhysics()
{
	this->enemyGroup->UpdatePhysics();
	this->projectileGroup->UpdatePhysics();
	this->simonGroup->UpdatePhysics();
}

void CVMap::LoadSimon(InfoPanel * infoPanel, GameOverScreen *goScreen, Simon * simon)
{

	infoPanel->Reset();
	this->enemyGroup->LoadSimon(simon);

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
	this->simonGroup->AddDrawObjectToList(goScreen);
	this->simon->body->allowWorldBlock = false;
	this->simon->body->allowWorldBound = false;
	this->simon->body->allowWorldBounciness = false;
	SetStage(0, 0, true);
}

void CVMap::OnSimonDeath()
{

}

void CVMap::SetStage(int stageNumber, int blockNumber,bool isRestartState)
{
	this->currentStage = this->stageList[stageNumber];
	SetBlock(blockNumber, isRestartState);
}

void CVMap::SetBlock(int blockNumber,bool isRestartState)
{
	if (this->currentBlock != nullptr) {
		this->currentBlock->Reset();
	}
	if (blockNumber == -1) {
		blockNumber = this->currentStage->blockList.size() - 1;
	}
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
		}
		if(simon->isClimbingLadder) this->SetSimonPositionOnChangeBlock();
	}
	this->simon->body->PreUpdate();

	this->camera->SetBlock(this->currentBlock);
	this->simon->SetBlock((*this->currentBlock));
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
	if (nextBlock == -1 
		//||(!this->simon->isClimbingLadder && this->simon->isGro)
		) {
		//OnFallOutOfMap();
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
	g_debug.Log("Simon fall out of map!");
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

void CVMap::DebugUpdate()
{
#ifdef DEBUG_ENABLE_SET_STAGE_BLOCK_KEY_CONTROL
	SAFE_BREAK_BEGIN
		if (this->currentTimeOutPressKey != nullptr) SAFE_BREAK
		auto input = this->cvGame->GetInput();
		if (input->KeyDown(this->debugStageKey[KeyControlSetStageBlock::PreviousBlock])) {
			this->currentTimeOutPressKey = this->add->TimeOut(150, [this]() {
				GoTo(true, false);
				this->currentTimeOutPressKey = nullptr;
			})->Start();
			SAFE_BREAK
		}

		if (input->KeyDown(this->debugStageKey[KeyControlSetStageBlock::NextBlock])) {
			this->currentTimeOutPressKey = this->add->TimeOut(150, [this]() {
				GoTo(true, true);
				this->currentTimeOutPressKey = nullptr;
			})->Start();
			SAFE_BREAK
		}

		if (input->KeyDown(this->debugStageKey[KeyControlSetStageBlock::PreviousStage])) {
			this->currentTimeOutPressKey = this->add->TimeOut(150, [this]() {
				GoTo(false, false);
				this->currentTimeOutPressKey = nullptr;
			})->Start();
			SAFE_BREAK
		}

		if (input->KeyDown(this->debugStageKey[KeyControlSetStageBlock::NextStage])) {
			this->currentTimeOutPressKey = this->add->TimeOut(150, [this]() {
				GoTo(false, true);
				this->currentTimeOutPressKey = nullptr;
			})->Start();
			SAFE_BREAK
		}
	SAFE_BREAK_END
#endif // DEBUG_ENABLE_SET_STAGE_BLOCK_KEY_CONTROL

}

void CVMap::CheckIfSimonOutOfBlock()
{
	if (isSwitchingStage) return;
	//if (!simon->isClimbingLadder) return;
	if (this->currentBlock == nullptr) return;
	Rect r = simon->body->GetRect();
	Rect i;
	if (!Rect::intersect(i, r, (*currentBlock))) {
		if (this->simon->GetBottom() > this->currentBlock->bottom) {
			OnFallOutOfMap();
		}
		else OnOutOfBlock();
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
	this->simon->body->allowWorldBound = false;
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
		this->simon->body->allowWorldBound = true;
		this->simon->body->immoveable = false;
		this->door->body->SetEnable(true);
		this->simon->body->allowGravity = true;
		this->door = nullptr;
		this->camera->Follow(this->simon);
		this->camera->SetBlock(this->currentBlock);
		this->simon->SetBlock((*this->currentBlock));
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

void CVMap::OnEnterBossBlock(EnemyBase *enemy)
{
	this->cvGame->camera->UnFollow();
	this->simon->SetBlock(this->cvGame->camera->GetNormalRect());
	this->infoPanel->SetEnemy(enemy);
	this->currentBoss = enemy;
}

void CVMap::Active()
{
	this->cvGame->world->AddGroup(this);
}

void CVMap::DeActive()
{
	this->cvGame->world->RemoveGroup(this);
}

void CVMap::Reset()
{
	this->currentBlock->Reset();
	this->enemyGroup->ResetRetriveList();
	this->projectileGroup->Reset();
	this->simonGroup->Reset();
}

void CVMap::OnLevelCompleted()
{
	if (this->name == "level-2") {
		this->cvGame->cvMapManager->StartMap("level-3",this->simon);
	}
	else {
		g_debug.Error("No next level for " + this->name);
	}
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

void CVMap::GoTo(bool isBlock, bool isNext)
{
	int modifier = isNext ? 1 : -1;
	int index = isBlock ? this->currentBlock->blockIndex : this->currentStage->stageIndex;
	index += modifier;
	int tempBlockIndex = 0;
	if (isBlock) {
		if (index >= (int)this->currentStage->blockList.size()) {
			isBlock = false;
			index = this->currentStage->stageIndex + 1;
		}
		else {
			if (index < 0) {
				index = this->currentStage->stageIndex - 1;
				if (index < 0) {
					index = 0;
				}
				isBlock = false;
				tempBlockIndex = -1;
				if (index == this->currentStage->stageIndex) {
					tempBlockIndex = 0;
				}
			}
		}
	}
	if (!isBlock) {
		if (index >= (int)this->stageList.size()) {
			index = 0;
		}
		if (index < 0) {
			index = 0;
		}
		SetStage(index, tempBlockIndex, false);
	}
	else {
		OnNextBlock(index);
	}
	ResetSimonPositionTo(this->currentBlock->simonSpawnPosition);
}

void CVMap::ResetSimonPositionTo(Vector position)
{
	this->simon->ResetState();
	this->simon->SetPosition(position, true);

}

