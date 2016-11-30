#include "HolyWaterItem.h"
#include "Simon.h"
#include "CharacterBase.h"

HolyWaterItem::HolyWaterItem(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

HolyWaterItem::~HolyWaterItem()
{
}

void HolyWaterItem::OnSimonContact(Simon * simon, ColliderArg e)
{
	//HolyWater *holyWater = new HolyWater(simon->)
	
	Destroy();
}
