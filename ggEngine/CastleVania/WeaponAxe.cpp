#include "WeaponAxe.h"
#include "CVAdd.h"


WeaponAxe::WeaponAxe(CVGame * cvGame, SpriteInfo * image) : WeaponBase(cvGame, image)
{
	this->body->allowGravity = true;
}

WeaponAxe::~WeaponAxe()
{
	//g_debug.Log("Deleting WeaponAxe");
}



void WeaponAxe::FireWeapon(bool isLeft)
{
	this->cvGame->add->LoopInfinity(300, [this] {
		
	})->Start();
	FireAsThrow(isLeft , this->throwForce);
}

void WeaponAxe::OnEnemyContact(EnemyBase * enemyBase, ColliderArg e)
{
}