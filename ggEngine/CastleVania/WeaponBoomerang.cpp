#include "WeaponBoomerang.h"
#include "CVAdd.h"

WeaponBoomerang::WeaponBoomerang(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: WeaponBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
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

	//if (this->contactedWorldBound == false) {
	//	this->cvGame->add->TimeOut(this->timeToReturn, [this] {
	//		Vector direction = GetHorizontalDirection(!this->isLeft);
	//		this->body->SetForce(this->throwForce, direction);
	//	})->Start();
	//}
}

void WeaponBoomerang::OnEnemyContact(EnemyBase * enemyBase, ColliderArg e)
{
}

void WeaponBoomerang::OnSimonContact(Simon * simon, ColliderArg e)
{
	this->Destroy();
}

