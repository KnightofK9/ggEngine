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
	WeaponDagger *weaponDagger = new WeaponDagger(this->cvGame, inf, 17, 9, 0, 1);
	weaponDagger->SetPosition(x, y);
	weaponDagger->SetParentObject(group);
	weaponDagger->Active();
	weaponDagger->CreateAnimation("fireAnim", 0, 0, true);
	weaponDagger->PlayAnimation("fireAnim");
	weaponDagger->FireWeapon(isLeft);

	group->AddDrawObjectToList(weaponDagger);
	return weaponDagger;
}

WeaponAxe* WeaponManager::AddWeaponAxe(double x, double y, bool isLeft, Group * group)
{
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::AXE_WEAPON_TEXTURE);
	WeaponAxe *weaponAxe = new WeaponAxe(this->cvGame, inf, 15, 14, 0, 4, 70);
	weaponAxe->SetPosition(x, y);
	weaponAxe->SetParentObject(group);
	weaponAxe->Active();
	weaponAxe->CreateAnimation("fireAnim", 0, 2, true);
	weaponAxe->PlayAnimation("fireAnim");
	weaponAxe->FireWeapon(isLeft);

	group->AddDrawObjectToList(weaponAxe);
	return weaponAxe;
}

WeaponHolyWater* WeaponManager::AddWeaponHolyWater(double x, double y, bool isLeft, Group * group)
{
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::HOLY_WATER_WEAPON_TEXTURE);
	WeaponHolyWater *weaponHolyWater = new WeaponHolyWater(this->cvGame, inf, 16, 13, 0, 3, 70);
	weaponHolyWater->SetPosition(x, y);
	weaponHolyWater->SetParentObject(group);
	weaponHolyWater->Active();
	weaponHolyWater->CreateAnimation("fireAnim", 0, 0, true);
	weaponHolyWater->CreateAnimation("brickContact", { 1, 2, 1, 2, 1, 2, 1 }, false)->SetOnCompleted([weaponHolyWater](Animator*) {
		weaponHolyWater->Destroy();
	});
	weaponHolyWater->FireWeapon(isLeft);
	weaponHolyWater->PlayAnimation("fireAnim");

	//weaponHolyWater->events->onCollide = [weaponHolyWater](GameObject *go, ColliderArg e) {
	//	GameObject *otherObject = e.colliderObject;
	//	Tag type = otherObject->tag;
	//	switch (type) {
	//	case ObjectType_LevelTwoBrick:
	//		weaponHolyWater->PlayAnimation("blockContact");
	//		break;
	//	default:
	//		return;
	//	}
	//};

	group->AddDrawObjectToList(weaponHolyWater);
	return weaponHolyWater;
}

WeaponBoomerang* WeaponManager::AddWeaponBoomerang(double x, double y, bool isLeft, Group * group)
{
	SpriteInfo *inf = this->cache->GetSpriteInfo(TextureConstant::BOOMERANG_WEAPON_TEXTURE);
	WeaponBoomerang *weaponBoomerang = new WeaponBoomerang(this->cvGame, inf, 15, 14, 0, 3, 70);
	weaponBoomerang->SetPosition(x, y);
	weaponBoomerang->SetParentObject(group);
	weaponBoomerang->Active();
	weaponBoomerang->CheckCollisionToSimon(this->cvGame->simon);
	weaponBoomerang->CreateAnimation("fireAnim", 0, 2, true);
	weaponBoomerang->PlayAnimation("fireAnim");
	weaponBoomerang->FireWeapon(isLeft);

	group->AddDrawObjectToList(weaponBoomerang);
	return weaponBoomerang;
}
