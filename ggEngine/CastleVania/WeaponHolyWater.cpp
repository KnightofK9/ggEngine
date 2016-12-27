#include "WeaponHolyWater.h"
#include "AudioManager.h"
#include "CVAdd.h"

WeaponHolyWater::WeaponHolyWater(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: WeaponBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->body->allowGravity = true;
}

WeaponHolyWater::~WeaponHolyWater()
{
	//g_debug.Log("Deleting WeaponHolyWater");
}



void WeaponHolyWater::FireWeapon(bool isLeft)
{
	FireAsThrow(isLeft, this->throwForce);
}

void WeaponHolyWater::OnBrickContact(GameObject * go, ColliderArg e)
{
	//g_debug.Log("Contacting Brick");
	this->PlayAnimation("brickContact");
	this->body->allowGravity = false;
	this->body->velocity = { 0, 0 };
	this->cvGame->audioManager->holyWaterSound->Play();
}

