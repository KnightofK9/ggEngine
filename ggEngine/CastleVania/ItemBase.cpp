#include "ItemBase.h"
#include "CVGame.h"
#include "Simon.h"
#include "CVAdd.h"
ItemBase::ItemBase(CVGame * cvGame, SpriteInfo * image) :CVSprite(cvGame, image)
{
	this->cvGame = cvGame;
	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(this->image->GetWidth(), this->image->GetHeight());
	this->body->allowGravity = true;
	this->body->allowWorldBound = false;
	this->events->onCollide = [this](GameObject *go, ColliderArg e) {
		Simon * simon = dynamic_cast<Simon*>(e.colliderObject);
		if (simon != nullptr) {
			OnSimonContact(simon,e);
		}
	};
	this->events->onCheckingCollide = [this](GameObject *go, ColliderArg e) {
		auto otherGo = e.colliderObject;
		Tag tag = otherGo->tag;
		switch (tag) {
		case ObjectType_LevelTwoBrick:
			return true;
		}
		return false;
	};
	this->tag = ObjectType_Item;
	this->visible = false;
	this->body->SetActive(false);
}



ItemBase::~ItemBase()
{
	if (cvGame->simon != nullptr) {
		cvGame->simon->body->RemoveCheckCollisionWith(this);
	}
	if (timeEvent != nullptr) timeEvent->Stop();
}

void ItemBase::SetLiveTime(unsigned int liveTime)
{
	this->liveTime = liveTime;
}

void ItemBase::CheckCollisionToSimon(Simon * simon)
{
	simon->body->CheckCollisionTo(this);
}

void ItemBase::OnSimonContact(Simon * simon, ColliderArg e)
{
	Destroy();
}


void ItemBase::Active()
{
	this->visible = true;
	this->body->SetActive(true);
	if (this->liveTime != -1) {
		this->timeEvent = this->cvGame->add->TimeOut(this->liveTime, [this]() {
			Destroy();
		});
	}
}
