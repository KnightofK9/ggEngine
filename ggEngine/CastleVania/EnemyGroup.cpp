#include "EnemyGroup.h"
#include "CVGame.h"
EnemyGroup::EnemyGroup(CVGame * cvGame) : CameraActiveGroup(cvGame)
{
}

EnemyGroup::~EnemyGroup()
{
}

void EnemyGroup::Update()
{
	CameraActiveGroup::Update();
	for (auto go : this->activeGameObjectList) {
		if (go->events != nullptr && go->events->onUpdate != nullptr) {
			go->events->onUpdate(go);
		}
	}
}
