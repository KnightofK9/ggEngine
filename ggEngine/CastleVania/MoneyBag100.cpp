#include "MoneyBag100.h"
#include "AudioManager.h"
#include "Simon.h"

MoneyBag100::MoneyBag100(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

MoneyBag100::~MoneyBag100()
{
}

void MoneyBag100::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->IncreaseScore(this->money);
	simon->audioManager->collectMoneySound->Play();
	Destroy();
}
