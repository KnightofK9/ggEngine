#include "Ghost.h"
#include "CVGame.h"
#include "Simon.h"
Ghost::Ghost(CVGame * cvGame, SpriteInfo * spriteInfo) : TweenEnemyBase(cvGame, spriteInfo, 16, 16, 0, 2, 200)
{
	this->name = "Ghost";
	this->CreateAnimation("move", { 0,1}, true);
	this->CreateAnimation("idle", 0, 0, false);
	this->body->immoveable = true;
	SetMoveX(40);
	SetMoveY(20);
	SetSpeed(50);
	this->simonDetectRange = 200;
	this->allowToDetectSimon = true;
	this->PlayAnimation("move");
}

Ghost::~Ghost()
{
}

void Ghost::RunLeft()
{
	if (this->currentTween == nullptr) {
		TweenEnemyBase::RunLeft();
		this->PlayAnimation("move");
		AddTween(true);
		this->isMoving = true;
	}
}

void Ghost::RunRight()
{
	if (this->currentTween == nullptr) {
		TweenEnemyBase::RunRight();
		this->PlayAnimation("move");
		AddTween(false);
		this->isMoving = true;
	}
}

void Ghost::Update()
{
	EnemyBase::Update();
}

void Ghost::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	EnemyBase::OnSimonEnterRange(simon, isLeft);
}



void Ghost::AddTween(bool isLeft)
{
	Vector moveTo = this->cvGame->simon->position;
	int modifier = 1;
	if (isLeft) modifier = -1;
	moveTo.x += modifier*Helper::GetRamdomIntNumber(minX, moveX);
	moveTo.y -= Helper::GetRamdomIntNumber(minY, moveY);
	this->currentTween = this->cvGame->add->MoveTo(this, moveTo, round(moveTo.x / speed) * DEFAULT_MS_PER_FRAME_FOR_ANIMATION)->SetOnFinish([=]() {
		this->currentTween = nullptr;
		this->isMoving = false;
	})->Start();
}
