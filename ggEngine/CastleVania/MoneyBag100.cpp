#include "MoneyBag100.h"
#include "AudioManager.h"
#include "AnimationManager.h"
#include "Simon.h"

MoneyBag100::MoneyBag100(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

MoneyBag100::~MoneyBag100()
{
}

void MoneyBag100::OnSimonContact(Simon * simon, ColliderArg e)
{
	this->cvGame->animationManager->AddText100(this->position.x, this->position.y);
	simon->IncreaseScore(this->money);
	simon->audioManager->collectMoneySound->Play();
	Destroy();
}
