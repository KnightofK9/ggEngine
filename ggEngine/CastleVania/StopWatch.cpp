#include "StopWatch.h"
#include "Simon.h"

StopWatch::StopWatch(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

StopWatch::~StopWatch()
{
}

void StopWatch::OnSimonContact(Simon * simon, ColliderArg e)
{
	Destroy();
}
