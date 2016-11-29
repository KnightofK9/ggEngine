#include "MoneyBag1000.h"
#include "Simon.h"

MoneyBag1000::MoneyBag1000(CVGame * cvgame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	:ItemBaseAnim(cvgame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{

}

MoneyBag1000::~MoneyBag1000()
{
}

void MoneyBag1000::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->IncreaseScore(this->money);
	Destroy();
}
