#include "Heart.h"
#include "Simon.h"
Heart::Heart(CVGame *cvgame, SpriteInfo * image): ItemBase(cvgame,image)
{
}

Heart::~Heart()
{
}

void Heart::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->GainHealth(healthGain);
	Destroy();
}
