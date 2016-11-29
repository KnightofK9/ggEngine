#include "InvinPotion.h"
#include "Simon.h"
#include "CVGame.h"
#include "CVAdd.h"

InvinPotion::InvinPotion(CVGame * cvgame, SpriteInfo * image) : ItemBase(cvgame, image)
{

}

InvinPotion::~InvinPotion()
{
}

void InvinPotion::OnSimonContact(Simon * simon, ColliderArg e)
{
	simon->SetVisible(false);
	this->cvGame->cvAdd->TimeOut(5000, [simon] {
		simon->SetVisible(true);
	})->Start();

	Destroy();
}
