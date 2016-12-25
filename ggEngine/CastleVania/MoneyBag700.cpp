#include "MoneyBag700.h"
#include "AudioManager.h"
#include "Simon.h"

MoneyBag700::MoneyBag700(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

MoneyBag700::~MoneyBag700()
{
}

void MoneyBag700::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->IncreaseScore(this->money);
	simon->audioManager->collectMoneySound->Play();
	Destroy();
}
