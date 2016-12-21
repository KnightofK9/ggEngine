#include "Candle.h"
#include "CVAdd.h"
#include "WeaponWhip.h"
#include "WeaponBase.h"
#include "ItemBase.h"


Candle::Candle(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: DropObjectBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
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


void Candle::Active()
{
	BreakableObjectBase::Active();
	this->PlayAnimation("candle");
}

