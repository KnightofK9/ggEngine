#include "Ghost.h"
#include "CVGame.h"
#include "Simon.h"
Ghost::Ghost(CVGame * cvGame, SpriteInfo * spriteInfo) : TweenEnemyBase(cvGame, spriteInfo, 16, 16, 0, 2, 400)
{
	this->CreateAnimation("move", { 0,1,2}, true);
	this->CreateAnimation("idle", 0, 0, false);
	SetMoveX(40);
	SetSpeed(0.5);
	this->allowToDetectSimon = true;
}

Ghost::~Ghost()
{
}

void Ghost::RunLeft()
{
	TweenEnemyBase::RunLeft();
	this->PlayAnimation("move");
	AddTween(true);
	this->isMoving = true;
}

void Ghost::RunRight()
{
	TweenEnemyBase::RunRight();
	this->PlayAnimation("move");
	AddTween(false);
	this->isMoving = true;
}

void Ghost::Update()
{
	EnemyBase::Update();
}

void Ghost::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	EnemyBase::OnSimonEnterRange(simon, isLeft);
	this->allowToDetectSimon = false;
}



void Ghost::AddTween(bool isLeft)
{
	Vector simon = this->cvGame->simon->position;
	Vector moveTo = simon;
	int modifier = 1;
	if (isLeft) modifier = -1;
	moveTo.x = this->position.x + modifier*moveX;
	this->cvGame->add->MoveTo(this, moveTo, round(moveX / speed) * DEFAULT_MS_PER_FRAME_FOR_ANIMATION, Easing::easeInQuad, Easing::easeOutQuad)->SetOnFinish([=]() {
		this->body->immoveable = false;
		this->body->velocity.x = modifier*speed;
	})->Start();
}
