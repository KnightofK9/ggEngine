#include "BreakableTileBrick.h"
#include "TypeEnum.h"
#include "CVGame.h"
#include "Simon.h"
#include "ItemBase.h"
BreakableTileBrick::BreakableTileBrick(CVGame * cvGame, SpriteInfo * image) : BreakableObjectBase(cvGame,image,16,16,0,1)
{
	this->tag = ObjectType_BreakableTileBrick;
}


BreakableTileBrick::~BreakableTileBrick()
{
}

void BreakableTileBrick::OnWeaponWhipContact(WeaponWhip * whip, ColliderArg e)
{
	DropItem();
	Destroy();
}

void BreakableTileBrick::OnSubWeaponContact(WeaponBase * weapon, ColliderArg e)
{
	Destroy();
}

void BreakableTileBrick::SetDropItem(std::string itemJson)
{
	this->itemJson = itemJson;
}

void BreakableTileBrick::Active()
{
	BreakableObjectBase::Active();
}

void BreakableTileBrick::Draw()
{
	BreakableObjectBase::Draw();
}

void BreakableTileBrick::DropItem()
{
	if (this->itemJson == "") return;
	auto go = this->cvGame->GetObjectInstance(this->itemJson.c_str(), this->cvGame->simon->GetGroupToCheckCollision());
	//auto itemBase = dynamic_cast<ItemBase*>(go);
	//itemBase->CheckCollisionToSimon(this->cvGame->simon);
}

