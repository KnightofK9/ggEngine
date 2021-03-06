#include "TripleShot.h"
#include "AudioManager.h"
#include "Simon.h"

TripleShot::TripleShot(CVGame *cvGame, SpriteInfo *image) : ItemBase(cvGame, image)
{

}

TripleShot::~TripleShot()
{
}

void TripleShot::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->SetShot(this->shot);
	simon->audioManager->collectWeaponSound->Play();
	Destroy();
}
