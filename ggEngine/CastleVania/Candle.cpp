#include "Candle.h"
#include "CVAdd.h"
#include "WeaponWhip.h"
#include "WeaponBase.h"
#include "ItemBase.h"


Candle::Candle(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: BreakableObjectBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->CreateAnimation("candle", 0, 1, true);
	this->body->rigidBody->height = 8;
	this->body->rigidBody->width = 16;
	this->tag = ObjectType_Candle;
}


Candle::~Candle()
{
}

void Candle::OnWeaponWhipContact(WeaponWhip * whip, ColliderArg e)
{
	DropItem();
	Destroy();
}

void Candle::OnSubWeaponContact(WeaponBase * weapon, ColliderArg e)
{
	Destroy();
}

void Candle::SetDropItem(std::string itemJson)
{
	this->itemJson = itemJson;
}

void Candle::Active()
{
	BreakableObjectBase::Active();
	this->PlayAnimation("candle");
}

void Candle::DropItem()
{
	if (this->itemJson == "") return;
	auto go = this->cvGame->GetObjectInstance(this->itemJson.c_str(),this->cvGame->simon->GetGroupToCheckCollision());
	auto itemBase = dynamic_cast<ItemBase*>(go);
	//itemBase->CheckCollisionToSimon(this->cvGame->simon);
}
