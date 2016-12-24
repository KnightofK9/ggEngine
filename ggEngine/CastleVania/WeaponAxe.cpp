#include "WeaponAxe.h"
#include "CVAdd.h"


WeaponAxe::WeaponAxe(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: WeaponBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->body->allowGravity = true;
}

WeaponAxe::~WeaponAxe()
{
	//g_debug.Log("Deleting WeaponAxe");
}



void WeaponAxe::FireWeapon(bool isLeft)
{
	FireAsThrow(isLeft , this->throwForce);
}