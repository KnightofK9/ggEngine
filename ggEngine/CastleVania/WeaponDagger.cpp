#include "WeaponDagger.h"

WeaponDagger::WeaponDagger(CVGame * cvGame, SpriteInfo * image) : WeaponBase(cvGame,image)
{

}

WeaponDagger::~WeaponDagger()
{

}



void WeaponDagger::FireWeapon(bool isLeft)
{
	FireHorizontal(isLeft);
}

void WeaponDagger::OnEnemyContact(EnemyBase * enemyBase, ColliderArg e)
{
}
