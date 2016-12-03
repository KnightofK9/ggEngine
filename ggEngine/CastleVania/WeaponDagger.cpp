#include "WeaponDagger.h"
#include "CVAdd.h"

WeaponDagger::WeaponDagger(CVGame * cvGame, SpriteInfo * image) : WeaponBase(cvGame,image)
{
	this->body->allowGravity = false;
}

WeaponDagger::~WeaponDagger()
{
	//g_debug.Log("Deleting WeaponDagger");
}



void WeaponDagger::FireWeapon(bool isLeft)
{
	Simon *simon = this->cvGame->simon;
	if (simon->GetHeartPoint() - this->heartConsumtion >= 0)
	{
		simon->DecreaseHeartPoint(this->heartConsumtion);
		FireHorizontal(isLeft, this->throwForce);
	}
}

void WeaponDagger::OnEnemyContact(EnemyBase * enemyBase, ColliderArg e)
{
}
