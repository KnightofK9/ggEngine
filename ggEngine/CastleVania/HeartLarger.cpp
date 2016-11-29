#include "HeartLarger.h"
#include "Simon.h"

HeartLarger::HeartLarger(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

HeartLarger::~HeartLarger()
{
}

void HeartLarger::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->IncreaseLifePoint(this->point);
	Destroy();
}
