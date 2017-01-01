#include "MoneyBag1000.h"
#include "AudioManager.h"
#include "Simon.h"
#include "AnimationManager.h"

MoneyBag1000::MoneyBag1000(CVGame * cvgame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	:ItemBaseAnim(cvgame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{

}

MoneyBag1000::~MoneyBag1000()
{
}

void MoneyBag1000::OnSimonContact(Simon * simon, ColliderArg e)
{
	this->cvGame->animationManager->AddText1000(this->position.x, this->position.y);
	simon->IncreaseScore(this->money);
	simon->audioManager->collectMoneySound->Play();
	Destroy();
}
