#include "Candle.h"
#include "CVAdd.h"
#include "WeaponWhip.h"
#include "WeaponBase.h"



Candle::Candle(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: BreakableObjectBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->CreateAnimation("candle", 0, 1, true);
	this->tag = ObjectType_Candle;
}


Candle::~Candle()
{
}

void Candle::OnWeaponWhipContact(WeaponWhip * whip, ColliderArg e)
{
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
