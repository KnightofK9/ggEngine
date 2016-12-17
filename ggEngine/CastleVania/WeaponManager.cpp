#include "WeaponManager.h"
#include "CVGame.h"
#include "CVAdd.h"
#include "TextureConstant.h"
WeaponManager::WeaponManager(CVGame * cvGame) : ManagerBase(cvGame)
{

}

WeaponManager::~WeaponManager()
{
}

WeaponWhip * WeaponManager::AddWeaponWhip(double x, double y, bool isLeft, Group * group)
{
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::MAIN_WEAPON_TEXTURE);
	WeaponWhip *weaponWhip = new WeaponWhip(this->cvGame, inf, 76, 27, 0, 9, 120);
	weaponWhip->SetPosition(x, y);
	if (group != nullptr) {
		weaponWhip->SetParentObject(group);
		group->AddDrawObjectToList(weaponWhip);
	}
	return weaponWhip;
}

WeaponBase * WeaponManager::AddWeapon(Simon *simon, double x, double y, bool isLeft, Group * group)
{
	WeaponBase *weapon;
	switch (simon->subWeapon)
	{
	case SimonSubWeaponType::SubWeapon_Axe:
		weapon = this->AddWeaponAxe(x, y, isLeft, group);
		break;

	case SimonSubWeaponType::SubWeapon_Boomerang:
		weapon = this->AddWeaponBoomerang(x, y, isLeft, group);
		break;

	case SimonSubWeaponType::SubWeapon_Dagger:
		weapon = this->AddWeaponDagger(x, y, isLeft, group);
		break;

	case SimonSubWeaponType::SubWeapon_HolyWater:
		weapon = this->AddWeaponHolyWater(x, y, isLeft, group);
		break;

	case SimonSubWeaponType::SubWeapon_StopWatch:
		return NULL;

	case SimonSubWeaponType::SubWeapon_None:
		return NULL;

	default:
		return NULL;
	}

	if (weapon->GetHeartConsumtion() <= simon->GetHeartPoint()) {
		simon->DecreaseHeartPoint(weapon->GetHeartConsumtion());
		return weapon;
	} else {
		weapon->Destroy();
		return NULL;
	}
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
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::HOLY_WATER_TEXTURE);
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
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::BOOMERANG_TEXTURE);
	WeaponBoomerang *weaponBoomerang = new WeaponBoomerang(this->cvGame, inf);
	weaponBoomerang->SetPosition(x, y);
	weaponBoomerang->SetParentObject(group);
	weaponBoomerang->Active();
	weaponBoomerang->FireWeapon(isLeft);
	group->AddDrawObjectToList(weaponBoomerang);
	return weaponBoomerang;
}
