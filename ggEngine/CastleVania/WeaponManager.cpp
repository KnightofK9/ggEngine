#include "WeaponManager.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "TextureConstant.h"
WeaponManager::WeaponManager(CVGame * cvGame)
{
	this->cvGame = cvGame;
	this->cvAdd = cvGame->cvAdd;
	this->cache = cvGame->cache;
}

WeaponManager::~WeaponManager()
{
}

WeaponDagger* WeaponManager::AddWeaponDagger(double x, double y, bool isLeft, Group * group)
{
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::DAGGER_TEXTURE);
	WeaponDagger *weaponDagger = new WeaponDagger(this->cvGame, inf);
	weaponDagger->SetPosition(x, y);
	
	weaponDagger->Active();
	weaponDagger->FireWeapon(isLeft);
	//moneyBag->CheckCollisionToSimon(this->cvGame->simon);
	group->AddDrawObjectToList(weaponDagger);
	return weaponDagger;
}
