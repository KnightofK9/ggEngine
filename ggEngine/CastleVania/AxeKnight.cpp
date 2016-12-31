#include "AxeKnight.h"

AxeKnight::AxeKnight(CVGame * cvGame, SpriteInfo * spriteInfo) : WalkingEnemyBase(cvGame,spriteInfo,16,32,0,3,200)
{
	this->name = "AxeKnight";
	this->CreateAnimation("Move", { 0,1,2,1 }, true);
	SetMoveForce(0.25);
	this->allowToDetectSimon = true;
	this->detectY = false;

	this->maxHealth = 2;
	this->damage = 2;
	this->point = 400;
}

AxeKnight::~AxeKnight()
{
}

