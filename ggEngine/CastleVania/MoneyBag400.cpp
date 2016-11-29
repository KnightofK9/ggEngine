#include "MoneyBag400.h"
#include "Simon.h"

MoneyBag400::MoneyBag400(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

MoneyBag400::~MoneyBag400()
{
}

void MoneyBag400::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->IncreaseScore(this->money);
	Destroy();
}
