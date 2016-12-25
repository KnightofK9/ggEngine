#include "Crown.h"
#include "AudioManager.h"
#include "Simon.h"

Crown::Crown(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

Crown::~Crown()
{
}

void Crown::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->infoPanel->item->SetImage(this->image);
	simon->audioManager->collectMoneySound->Play();
	Destroy();
}
