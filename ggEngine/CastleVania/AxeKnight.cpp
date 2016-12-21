#include "AxeKnight.h"

AxeKnight::AxeKnight(CVGame * cvGame, SpriteInfo * spriteInfo) : WalkingEnemyBase(cvGame,spriteInfo,16,32,0,3,200)
{
	this->CreateAnimation("Move", { 0,1,2,1 }, true);
	SetMoveForce(0.25);
}

AxeKnight::~AxeKnight()
{
}

void AxeKnight::RunLeft()
{
	WalkingEnemyBase::RunLeft();
	this->PlayAnimation("Move");
}

void AxeKnight::RunRight()
{
	WalkingEnemyBase::RunRight();
	this->PlayAnimation("Move");
}
