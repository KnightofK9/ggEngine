#include "WeaponBase.h"


WeaponBase::WeaponBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CVSpriteAnimation(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->cvGame = cvGame;
	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(this->image->GetWidth(), this->image->GetHeight());
	this->body->allowGravity = true;
	this->events->onCollide = [this](GameObject *go, ColliderArg e) {

	};
	this->tag = ObjectType_Simon;
	this->visible = false;
	this->body->SetActive(false);
}


WeaponBase::~WeaponBase()
{
}

void WeaponBase::Active()
{
	this->visible = true;
	this->body->SetActive(true);
}

void WeaponBase::Destroy()
{

}
