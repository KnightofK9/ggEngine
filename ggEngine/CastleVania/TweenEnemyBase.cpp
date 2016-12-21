#include "TweenEnemyBase.h"

TweenEnemyBase::TweenEnemyBase(CVGame * cvGame, SpriteInfo * spriteInfo, int frameWidth, int frameHeight, int defaultFrame, int numberOfFrame, DWORD msPerFrame) : 
	EnemyBase(cvGame, spriteInfo, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame)
{
	this->body->immoveable = false;
	this->body->allowGravity = false;
	//this->moveY = GetHeight();
}

TweenEnemyBase::~TweenEnemyBase()
{
}

void TweenEnemyBase::RunLeft()
{
	ChangeFacingDirection(true);
	this->body->velocity.x = -this->speed;
	this->isMoving = true;
}

void TweenEnemyBase::RunRight()
{
	ChangeFacingDirection(false);
	this->body->velocity.x = this->speed;
	this->isMoving = true;
}

void TweenEnemyBase::Update()
{
	if (isMoving) {
		double x = this->position.x - this->startPosition.x;
		double increaseY = this->moveY*(sin(x*moveX));
		this->position.y = this->startPosition.y + increaseY;
	}
	
}

void TweenEnemyBase::SetMoveY(double moveY)
{
	this->moveY = moveY;
}

void TweenEnemyBase::SetMoveX(double moveX)
{
	this->moveX = moveX;
}

void TweenEnemyBase::SetSpeed(double speed)
{
	this->speed = speed;
}

double TweenEnemyBase::GetSpeed()
{
	return this->speed;
}

void TweenEnemyBase::SetPosition(Vector position)
{
	this->startPosition = position;
	GameObject::SetPosition(position);
}
