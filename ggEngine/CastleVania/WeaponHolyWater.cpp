#include "WeaponHolyWater.h"
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

void WeaponHolyWater::OnEnemyContact(EnemyBase * enemyBase, ColliderArg e)
{
}

void WeaponHolyWater::OnBrickContact(GameObject * go, ColliderArg e)
{
	//this->PlayAnimation("brickContact");
}

