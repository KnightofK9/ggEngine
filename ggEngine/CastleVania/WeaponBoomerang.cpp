#include "WeaponBoomerang.h"
#include "CVAdd.h"

WeaponBoomerang::WeaponBoomerang(CVGame * cvGame, SpriteInfo * image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: WeaponBase(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->body->allowGravity = false;
}

WeaponBoomerang::~WeaponBoomerang()
{
	//g_debug.Log("Deleting WeaponBoomerang");
}



void WeaponBoomerang::FireWeapon(bool isLeft)
{
	this->isLeft = isLeft;
	int desX = this->distanceToReturn;
	if (isLeft) desX *= -1;


	this->tweenOut = this->cvGame->add->Tween(this->position.x, this->position.x + desX, this->timeToReturn, Easing::linearTween)->SetOnFinish([this]() {
		//this->preReturn();
		this->SetScale(-1, 1);
		int desX = 1000;
		if (!this->isLeft) desX *= -1;
		this->tweenReturn = this->cvGame->add->Tween(this->position.x, this->position.x + desX, 13000, Easing::linearTween)->Start();
	})->Start();

	

}

void WeaponBoomerang::OnSimonContact(ColliderArg e)
{
	//this->tweenOut->Stop();
	if (this->tweenReturn != nullptr) {
		this->tweenReturn->Stop();
		this->Destroy();
	}
}

void WeaponBoomerang::OnOutOfCamera(EventArg e)
{
	if (this->tweenReturn != nullptr) {
		this->tweenReturn->Stop();
		this->Destroy();
	}
	else {
		this->tweenOut->Stop();
		this->SetScale(-1, 1);

		int desX = 1000;
		if (!this->isLeft) desX *= -1;
		this->tweenReturn = this->cvGame->add->Tween(this->position.x, this->position.x + desX, 13000, Easing::linearTween)->Start();
	}
}

void WeaponBoomerang::SetPreparerForReturn(std::function<void()> preReturn)
{
	this->preReturn = preReturn;
}

