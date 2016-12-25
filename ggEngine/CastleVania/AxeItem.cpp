#include "AxeItem.h"
#include "AudioManager.h"
#include "Simon.h"

AxeItem::AxeItem(CVGame *cvGame, SpriteInfo *image) : ItemBase(cvGame, image)
{

}

AxeItem::~AxeItem()
{
}

void AxeItem::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->SetSubWeapon(SimonSubWeaponType::SubWeapon_Axe, this->image);
	simon->audioManager->collectWeaponSound->Play();
	Destroy();
}
