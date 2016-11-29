#include "AxeItem.h"
#include "Simon.h"

AxeItem::AxeItem(CVGame *cvGame, SpriteInfo *image) : ItemBase(cvGame, image)
{

}

AxeItem::~AxeItem()
{
}

void AxeItem::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->SetSubWeapon(NULL, this->image);
	Destroy();
}
