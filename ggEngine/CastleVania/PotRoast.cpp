#include "PotRoast.h"
#include "AudioManager.h"
#include "Simon.h"

PotRoast::PotRoast(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

PotRoast::~PotRoast()
{
}

void PotRoast::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->GainHealth(this->healthPoint);
	simon->audioManager->collectWeaponSound->Play();
	Destroy();
}
