#include "WeaponHolyWater.h"
#include "CVAdd.h"

WeaponHolyWater::WeaponHolyWater(CVGame * cvGame, SpriteInfo * image) : WeaponBase(cvGame,image)
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
