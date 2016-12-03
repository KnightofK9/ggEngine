#include "WeaponBoomerang.h"
#include "CVAdd.h"

WeaponBoomerang::WeaponBoomerang(CVGame * cvGame, SpriteInfo * image) : WeaponBase(cvGame, image)
{
	this->body->allowGravity = false;
	this->events->onWorldBounds = [this](GameObject *go, ColliderArg e) {
		this->contactedWorldBound = true;
		Vector direction = GetHorizontalDirection(!this->isLeft);
		this->body->AddForce(throwForce, direction);
	};
}

WeaponBoomerang::~WeaponBoomerang()
{
	//g_debug.Log("Deleting WeaponBoomerang");
}



void WeaponBoomerang::FireWeapon(bool isLeft)
{
	this->isLeft = isLeft;
	FireHorizontal(isLeft, this->throwForce);

	if (this->contactedWorldBound == false) {
		this->cvGame->cvAdd->TimeOut(this->timeToReturn, [this] {
			Vector direction = GetHorizontalDirection(!this->isLeft);
			this->body->SetForce(this->throwForce, direction);
		})->Start();
	}
}

void WeaponBoomerang::OnEnemyContact(EnemyBase * enemyBase, ColliderArg e)
{
}

