#include "WeaponDagger.h"
#include "CVAdd.h"

WeaponDagger::WeaponDagger(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: WeaponBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->body->allowGravity = false;
}

WeaponDagger::~WeaponDagger()
{
	//g_debug.Log("Deleting WeaponDagger");
}



void WeaponDagger::FireWeapon(bool isLeft)
{
	FireHorizontal(isLeft, this->throwForce);
}

