#include "Medusa.h"
#include "CVGame.h"
#include "Simon.h"
Medusa::Medusa(CVGame * cvGame, SpriteInfo * spriteInfo) : TweenEnemyBase(cvGame,spriteInfo,16,16,0,2,400)
{
	this->name = "MedusaHead";
	this->CreateAnimation("move", { 0,1,1 }, true);
	this->CreateAnimation("idle", 0, 0, false);
	SetMoveY(10);
	SetMoveX(0.5);
	SetSpeed(0.25);
	this->allowToDetectSimon = true;
}

Medusa::~Medusa()
{
}

void Medusa::RunLeft()
{
	TweenEnemyBase::RunLeft();
	this->PlayAnimation("move");
}

void Medusa::RunRight()
{
	TweenEnemyBase::RunRight();
	this->PlayAnimation("move");
}

void Medusa::Update()
{
	TweenEnemyBase::Update();
}

