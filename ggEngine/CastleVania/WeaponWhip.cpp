#include "WeaponWhip.h"
#include "CVGame.h"



WeaponWhip::WeaponWhip(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame)
	: CVSpriteAnimation(cvGame, image, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->SetAnchor(0.6, 0.3);
	this->SetScale(1, 1);
	this->CreateAnimation("1", 0, 2, false);	//standardWhip
	this->CreateAnimation("2", 3, 5, false);	//shortWhip
	this->CreateAnimation("3", 6, 8, false);	//longWhip

	this->cvGame->physics->EnablePhysics(this);
	this->body->CreateRectangleRigidBody(50, 50);
	this->body->allowGravity = false;
	this->body->allowWorldBound = false;

	this->cvGame->eventManager->EnableSpriteAnimationEvent(this);
	this->events->onAnimationCompleted = [this](GameObject *go, AnimationArg e) {
		//this->Destroy();
	};
	this->whipVersion = 1;
}


WeaponWhip::~WeaponWhip()
{
}

void WeaponWhip::UpgradeWhip()
{
	this->whipVersion++;
	if (this->whipVersion > 3)
		this->whipVersion = 1;
}

void WeaponWhip::Attack(bool isLeft)
{
	if (!isLeft)
		this->SetScale(-1, 1);
	this->PlayAnimation(std::to_string(this->whipVersion));
}
