#include "Stuff.h"
#include "Simon.h"

Stuff::Stuff(CVGame * cvgame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	:ItemBaseAnim(cvgame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
}

Stuff::~Stuff()
{
}

void Stuff::OnSimonContact(Simon * simon, ColliderArg e)
{
	Destroy();
}
