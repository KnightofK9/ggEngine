#include "DropObjectBase.h"
#include "CVGame.h"
#include "Simon.h"
#include "CVMap.h"
#include "EnemyGroup.h"
#include "Constant.h"
DropObjectBase::DropObjectBase(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: BreakableObjectBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
}

DropObjectBase::~DropObjectBase()
{
}

void DropObjectBase::OnWeaponWhipContact(WeaponWhip * whip, ColliderArg e)
{
	DropItem();
	BreakableObjectBase::OnWeaponWhipContact(whip, e);
}

void DropObjectBase::OnSubWeaponContact(WeaponBase * weapon, ColliderArg e)
{
	DropItem();
	BreakableObjectBase::OnSubWeaponContact(weapon, e);
}

void DropObjectBase::SetDropItem(std::string itemJson)
{
	this->itemJson = itemJson;
}
void DropObjectBase::DropItem()
{
	if (this->itemJson == "") return;
	auto go = this->cvGame->GetObjectInstance(this->itemJson.c_str(), this->cvGame->simon->currentMap->enemyGroup);
	if (go->body != nullptr) {
		go->body->PreUpdate();
	}
	if (go->events == nullptr) {
		go->events = new Events(this->cvGame,go);
	}
	auto timeOutEvent = this->game->add->TimeOut(Constant::LIVE_TIME_ITEM, [=]() {
		go->Destroy();
	})->Start();
	go->events->onDestroy = [=](GameObject*,EventArg) {
		timeOutEvent->Stop();
	};
	//auto itemBase = dynamic_cast<ItemBase*>(go);
	//itemBase->CheckCollisionToSimon(this->cvGame->simon);
}
