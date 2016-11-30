#include "Heart.h"
#include "Simon.h"
#include "CVGame.h"
Heart::Heart(CVGame *cvgame, SpriteInfo * image): ItemBase(cvgame,image)
{
	//audio = cvGame->cvAdd->Audio("Resource//Test//sound.wav");
}

Heart::~Heart()
{
}

void Heart::OnSimonContact(Simon * simon, ColliderArg e)
{
	//simon->GainHealth(healthGain);
	simon->IncreaseLifePoint(this->point);
	Destroy();
}
