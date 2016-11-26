#include "ItemBase.h"
#include "CVGame.h"
#include "Simon.h"
#include "CVAdd.h"
ItemBase::ItemBase(CVGame * cvGame, SpriteInfo * image) :CVSprite(cvGame->GetDrawManager(), image)
{
	this->cvGame = cvGame;
	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(this->image->GetWidth(), this->image->GetHeight());
	this->events->onCollide = [this](GameObject *go, ColliderArg e) {
		Simon * simon = dynamic_cast<Simon*>(go);
		if (go != nullptr) {
			OnSimonContact(simon,e);
		}
	};
	this->visible = false;
	this->body->SetActive(false);
}
ItemBase::~ItemBase()
{
}

void ItemBase::SetLiveTime(unsigned int liveTime)
{
	this->liveTime = liveTime;
}

void ItemBase::CheckCollisionToSimon(Simon * simon)
{
	this->body->CheckCollisionTo(simon);
}

void ItemBase::OnSimonContact(Simon * simon, ColliderArg e)
{
}

void ItemBase::Destroy()
{
	GameObject::Destroy();
}

void ItemBase::Active()
{
	this->visible = true;
	this->body->SetActive(true);
	if (this->liveTime != -1) {
		this->cvGame->cvAdd->TimeOut(this->liveTime, [this]() {
			Destroy();
		});
	}
}
