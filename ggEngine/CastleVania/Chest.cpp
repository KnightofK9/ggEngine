#include "Chest.h"
#include "AudioManager.h"
#include "Simon.h"

Chest::Chest(CVGame * cvgame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	:ItemBaseAnim(cvgame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
}


Chest::~Chest()
{
}

void Chest::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->audioManager->collectMoneySound->Play();
	Destroy();
}
