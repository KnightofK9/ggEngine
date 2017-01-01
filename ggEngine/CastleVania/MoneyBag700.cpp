#include "MoneyBag700.h"
#include "AudioManager.h"
#include "Simon.h"
#include "AnimationManager.h"

MoneyBag700::MoneyBag700(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

MoneyBag700::~MoneyBag700()
{
}

void MoneyBag700::OnSimonContact(Simon * simon, ColliderArg e)
{
	this->cvGame->animationManager->AddText700(this->position.x, this->position.y);
	simon->IncreaseScore(this->money);
	simon->audioManager->collectMoneySound->Play();
	Destroy();
}
