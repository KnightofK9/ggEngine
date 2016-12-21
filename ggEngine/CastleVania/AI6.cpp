#include "AI6.h"
#include "TypeEnum.h"
AI6::AI6(CVGame * cvGame, SpriteInfo * spriteInfo) : TweenEnemyBase(cvGame,spriteInfo,32,8)
{
	SetSpeed(0.5);
	this->body->rigidBody->SetAnchor(0.5, 0);
	this->body->immoveable = true;
	this->body->allowGravity = false;
	this->body->SetPhysicsMode(PhysicsMode_AABB);
	this->isRunning = false;
	this->tag = ObjectType_AI6;
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

void AI6::OnBrickContact(TileBrick * brick, ColliderArg e)
{
	if (e.blockDirection.left) RunRight();
	else RunLeft();
}

