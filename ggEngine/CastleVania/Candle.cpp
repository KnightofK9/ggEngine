#include "Candle.h"
#include "CVAdd.h"
#include "WeaponWhip.h"
#include "WeaponBase.h"



Candle::Candle(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CVSpriteAnimation(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(8, 16);
	this->body->allowGravity = false;

	this->events->onCollide = [this](GameObject *go, ColliderArg e) {
		WeaponWhip *whip = dynamic_cast<WeaponWhip*>(e.colliderObject);
		if (whip != nullptr) {
			OnWeaponWhipContact(whip, e);
			return;
		}

		WeaponBase *weapon = dynamic_cast<WeaponBase*>(e.colliderObject);
		if (weapon != nullptr) {
			OnSubWeaponContact(weapon, e);
			return;
		}
	};

	this->CreateAnimation("candle", 0, 1, true);
	this->PlayAnimation("candle");

	this->tag = ObjectType_Item;
	this->visible = false;
	this->body->SetActive(false);
}


Candle::~Candle()
{
}

void Candle::CheckCollisionToWeaponWhip(WeaponWhip * whip)
{
	whip->body->CheckCollisionTo(this);
}

void Candle::OnWeaponWhipContact(WeaponWhip * whip, ColliderArg e)
{
	this->Destroy();
}

void Candle::CheckCollisionToSubWeapon(WeaponBase * weapon)
{
	weapon->body->CheckCollisionTo(this);
}

void Candle::OnSubWeaponContact(WeaponBase * weapon, ColliderArg e)
{
	this->Destroy();
}

void Candle::Active()
{
	this->visible = true;
	this->body->SetActive(true);
}
