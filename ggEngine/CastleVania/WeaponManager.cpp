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
	weaponDagger->SetParentObject(group);
	weaponDagger->Active();
	weaponDagger->FireWeapon(isLeft);
	//moneyBag->CheckCollisionToSimon(this->cvGame->simon);
	group->AddDrawObjectToList(weaponDagger);
	return weaponDagger;
}

WeaponAxe* WeaponManager::AddWeaponAxe(double x, double y, bool isLeft, Group * group)
{
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::AXE_TEXTURE);
	WeaponAxe *weaponAxe = new WeaponAxe(this->cvGame, inf);
	weaponAxe->SetPosition(x, y);
	weaponAxe->SetParentObject(group);
	weaponAxe->Active();
	weaponAxe->FireWeapon(isLeft);
	//moneyBag->CheckCollisionToSimon(this->cvGame->simon);
	group->AddDrawObjectToList(weaponAxe);
	return weaponAxe;
}

WeaponHolyWater* WeaponManager::AddWeaponHolyWater(double x, double y, bool isLeft, Group * group)
{
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::AXE_TEXTURE);
	WeaponHolyWater *weaponHolyWater = new WeaponHolyWater(this->cvGame, inf);
	weaponHolyWater->SetPosition(x, y);
	weaponHolyWater->SetParentObject(group);
	weaponHolyWater->Active();
	weaponHolyWater->FireWeapon(isLeft);
	//moneyBag->CheckCollisionToSimon(this->cvGame->simon);
	group->AddDrawObjectToList(weaponHolyWater);
	return weaponHolyWater;
}

WeaponBoomerang* WeaponManager::AddWeaponBoomerang(double x, double y, bool isLeft, Group * group)
{
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::AXE_TEXTURE);
	WeaponBoomerang *weaponBoomerang = new WeaponBoomerang(this->cvGame, inf);
	weaponBoomerang->SetPosition(x, y);
	weaponBoomerang->SetParentObject(group);
	//weaponBoomerang->Active();
	//weaponBoomerang->FireWeapon(isLeft);
	//moneyBag->CheckCollisionToSimon(this->cvGame->simon);
	group->AddDrawObjectToList(weaponBoomerang);
	return weaponBoomerang;
}
