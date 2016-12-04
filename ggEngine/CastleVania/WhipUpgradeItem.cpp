#include "WhipUpgradeItem.h"
#include "Simon.h"

WhipUpgradeItem::WhipUpgradeItem(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

WhipUpgradeItem::~WhipUpgradeItem()
{
}

void WhipUpgradeItem::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->UpgradeWhip();
	Destroy();
}
