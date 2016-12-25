#include "StopWatch.h"
#include "AudioManager.h"
#include "Simon.h"

StopWatch::StopWatch(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

StopWatch::~StopWatch()
{
}

void StopWatch::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->SetSubWeapon(SimonSubWeaponType::SubWeapon_StopWatch, this->image);
	simon->audioManager->collectWeaponSound->Play();
	Destroy();
}
