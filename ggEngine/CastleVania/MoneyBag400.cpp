#include "MoneyBag400.h"
#include "AudioManager.h"
#include "Simon.h"
#include "AnimationManager.h"

MoneyBag400::MoneyBag400(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

MoneyBag400::~MoneyBag400()
{
}

void MoneyBag400::OnSimonContact(Simon * simon, ColliderArg e)
{
	this->cvGame->animationManager->AddText400(this->position.x, this->position.y);
	simon->IncreaseScore(this->money);
	simon->audioManager->collectMoneySound->Play();
	Destroy();
}
