#include "DoubleShot.h"
#include "AudioManager.h"
#include "Simon.h"

DoubleShot::DoubleShot(CVGame *cvGame, SpriteInfo *image) : ItemBase(cvGame, image)
{

}

DoubleShot::~DoubleShot()
{
}

void DoubleShot::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->SetShot(this->shot);
	simon->audioManager->collectWeaponSound->Play();
	Destroy();
}
