#include "SimonGroup.h"
#include "CVGame.h"
SimonGroup::SimonGroup(CVGame * cvGame) : Group(cvGame)
{
}

SimonGroup::~SimonGroup()
{
}

void SimonGroup::CheckCollisionTo(std::list<GameObject*> staticGoList)
{
	//for (auto go : this->drawList) {
	//	if (go->body != nullptr) {
	//		go->body->AddListCheckCollisionTo(staticGoList);
	//	}
	//}
}

void SimonGroup::Reset()
{
	this->drawList.clear();
}
