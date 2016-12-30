#include "AI6.h"
#include "TypeEnum.h"
AI6::AI6(CVGame * cvGame, SpriteInfo * spriteInfo) : TweenEnemyBase(cvGame,spriteInfo,32,8)
{
	this->name = "AI6";
	SetSpeed(0.5);
	SetAnchor(0, 0);
	this->body->rigidBody->SetAnchor(0, 0);
	this->body->SetActive(false);
	this->body->immoveable = true;
	this->body->allowGravity = false;
	this->body->SetPhysicsMode(PhysicsMode_AABB);
	this->isRunning = false;
	this->tag = ObjectType_AI6;
	this->events->onOutOfCamera = nullptr;
}

AI6::~AI6()
{
}

void AI6::RunLeft()
{
	this->isLeft = true;
	this->isRunning = true;
}

void AI6::RunRight()
{
	this->isLeft = false;
	this->isRunning = true;
}

void AI6::Update()
{
	if (this->isRunning) {
		if (this->position.x <= this->startPosition.x) {
			RunRight();
		}
		else if (this->position.x + this->GetWidth() >= this->startPosition.x + this->moveWidth) {
			RunLeft();
		}
		if(this->isLeft)
			this->position.x -= this->speed;
		else
			this->position.x += this->speed;
	}
}

void AI6::Active()
{
	EnemyBase::Active();
	RunLeft();
}

void AI6::SetMoveWidth(double moveWidth)
{
	this->moveWidth = moveWidth;
}

void AI6::SetPosition(Vector position)
{
	GameObject::SetPosition(position);
	this->startPosition = position;
}

