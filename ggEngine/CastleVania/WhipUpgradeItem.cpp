#include "WhipUpgradeItem.h"
#include "AudioManager.h"
#include "CVAdd.h"

WhipUpgradeItem::WhipUpgradeItem(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

WhipUpgradeItem::~WhipUpgradeItem()
{
}

void WhipUpgradeItem::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->UpgradeWhip();
	simon->audioManager->collectWeaponSound->Play();
	Destroy();
}
