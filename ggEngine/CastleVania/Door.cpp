#include "Door.h"
#include "TypeEnum.h"
#include "AudioManager.h"
#include "CVGame.h"
Door::Door(CVGame * cvGame, SpriteInfo * image) : CVSpriteAnimation(cvGame, image, 22, 48, 0, 3)
{
	this->tag = ObjectType_Door;
	cvGame->physics->AttachBodyTo(this);
	this->body->CreateRectangleRigidBody(GetWidth(), GetHeight());
	this->body->immoveable = true;
	this->SetAnchor(0.5, 0);
	this->CreateAnimation("OpenDoor", 0, 2, false);
	this->CreateAnimation("CloseDoor", { 2,1,0 }, false);
}

Door::~Door()
{
}

void Door::OpenDoor(bool isLeft)
{
	SetFacingDirection(isLeft);
	this->cvGame->audioManager->openDoorSound->Play();
	this->PlayAnimation("OpenDoor");
}

void Door::CloseDoor()
{
	SetFacingDirection(isLeft);
	this->PlayAnimation("CloseDoor");
}

void Door::ResetDoor()
{
	this->PlayAnimation("default");
}

void Door::SetFacingDirection(bool isLeft)
{
	this->isLeft = isLeft;
}
