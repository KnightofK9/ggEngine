#include "MedusaHead.h"
#include "CVGame.h"
#include "Simon.h"
MedusaHead::MedusaHead(CVGame * cvGame, SpriteInfo * spriteInfo) : TweenEnemyBase(cvGame,spriteInfo,16,16,0,2,400)
{
	this->name = "MedusaHead";
	this->CreateAnimation("move", { 0,1 }, true);
	this->CreateAnimation("idle", 0, 0, false);
	SetMoveY(30);
	SetMoveX(0.05);
	SetSpeed(1);
	this->allowToDetectSimon = true;
}

MedusaHead::~MedusaHead()
{
}

void MedusaHead::RunLeft()
{
	TweenEnemyBase::RunLeft();
	this->PlayAnimation("move");
}

void MedusaHead::RunRight()
{
	TweenEnemyBase::RunRight();
	this->PlayAnimation("move");
}

void MedusaHead::Update()
{
	TweenEnemyBase::Update();
}

void MedusaHead::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	TweenEnemyBase::OnSimonEnterRange(simon, isLeft);
	this->allowToDetectSimon = false;
}

