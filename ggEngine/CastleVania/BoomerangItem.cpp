#include "BoomerangItem.h"
#include "Simon.h"

BoomerangItem::BoomerangItem(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

BoomerangItem::~BoomerangItem()
{
}

void BoomerangItem::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->SetSubWeapon(SimonSubWeaponType::SubWeapon_Boomerang, this->image);
	Destroy();
}
