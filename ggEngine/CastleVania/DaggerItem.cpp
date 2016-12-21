#include "DaggerItem.h"
#include "Simon.h"

DaggerItem::DaggerItem(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

DaggerItem::~DaggerItem()
{
}

void DaggerItem::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->SetSubWeapon(SimonSubWeaponType::SubWeapon_Dagger, this->image);
	Destroy();
}
