#include "HeartLarger.h"
#include "Simon.h"
#include "AudioManager.h"

HeartLarger::HeartLarger(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

HeartLarger::~HeartLarger()
{
}

void HeartLarger::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->IncreaseHeartPoint(this->point);
	simon->audioManager->collectHeartSound->Play();
	Destroy();
}
