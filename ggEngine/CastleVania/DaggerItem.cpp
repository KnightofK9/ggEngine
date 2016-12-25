#include "DaggerItem.h"
#include "AudioManager.h"
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
	simon->audioManager->collectWeaponSound->Play(); 
	Destroy();
}
