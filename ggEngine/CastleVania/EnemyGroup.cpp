#include "EnemyGroup.h"
#include "CVGame.h"
#include "EnemyBase.h"
#include "Simon.h"
EnemyGroup::EnemyGroup(CVGame * cvGame) : CameraActiveGroup(cvGame)
{
}

EnemyGroup::~EnemyGroup()
{
}

void EnemyGroup::Update()
{
	CameraActiveGroup::Update();
	UpdateRetriveEnemy();
	for (auto go : this->activeGameObjectList) {
		if (go->events != nullptr && go->events->onUpdate != nullptr) {
			go->events->onUpdate(go);
		}
	}
}

void EnemyGroup::AddEnemyToRetriveList(EnemyBase * enemy)
{
	this->retriveEnemyList.push_back(enemy);
}

void EnemyGroup::RemoveEnemyFromRetriveList(EnemyBase * enemy)
{
	this->retriveEnemyList.remove(enemy);
}

void EnemyGroup::ResetRetriveList()
{
	this->retriveEnemyList.clear();
}

void EnemyGroup::LoadSimon(Simon * simon)
{
	this->simon = simon;
}

void EnemyGroup::UpdateRetriveEnemy()
{
	Rect r = this->game->camera->GetNormalRect();
	for (auto it = this->retriveEnemyList.begin(); it != this->retriveEnemyList.end();) {
		auto enemy = (*it);
		if (!enemy->IsInRect(r) 
			&& (abs(enemy->position.x - this->simon->position.x) > enemy->simonMinRespawnDistance
				|| abs(enemy->position.y - this->simon->position.y) > enemy->simonMinRespawnDistance
				)) {
			enemy->Revive();
			this->retriveEnemyList.erase(it++);
		}
		else {
			++it;
		}
	}
}
