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
	//simon->SetVisible(false);
	simon->SetOpacity(100);
	this->cvGame->add->TimeOut(5000, [simon] {
		simon->SetOpacity(255);
	})->Start();

	Destroy();
}
