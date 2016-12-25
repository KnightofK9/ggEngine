#include "BreakableObjectBase.h"
#include "CVAdd.h"
#include "WeaponWhip.h"
#include "WeaponBase.h"
#include "CVBlock.h"

BreakableObjectBase::BreakableObjectBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CVSpriteAnimation(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(GetWidth(), GetHeight());
	this->body->allowGravity = false;

	this->events->onCollide = [this](GameObject *go, ColliderArg e) {
		auto otherObject = e.colliderObject;
		Tag tag = otherObject->tag;
		switch (tag) {
		case ObjectType_Weapon:
			OnWeaponWhipContact(dynamic_cast<WeaponWhip*>(otherObject), e);
			break;
		case ObjectType_SubWeapon:
			OnSubWeaponContact(dynamic_cast<WeaponBase*>(otherObject), e);
			break;
		}
		/*WeaponWhip *whip = dynamic_cast<WeaponWhip*>(e.colliderObject);
		if (whip != nullptr) {
			OnWeaponWhipContact(whip, e);
			return;
		}

		WeaponBase *weapon = dynamic_cast<WeaponBase*>(e.colliderObject);
		if (weapon != nullptr) {
			OnSubWeaponContact(weapon, e);
			return;
		}*/
	};
	this->tag = ObjectType_Item;
	this->visible = false;
	this->body->SetActive(false);
}


BreakableObjectBase::~BreakableObjectBase()
{
}


void BreakableObjectBase::OnWeaponWhipContact(WeaponWhip * whip, ColliderArg e)
{
	Kill();
}


void BreakableObjectBase::OnSubWeaponContact(WeaponBase * weapon, ColliderArg e)
{
	Kill();
}

void BreakableObjectBase::Active()
{
	this->visible = true;
	this->body->SetActive(true);
}

void BreakableObjectBase::Kill()
{
	this->cvGame->simon->currentMap->GetCurrentBlock()->AddObjectToRevivedList(this);
	GameObject::Kill();
}
