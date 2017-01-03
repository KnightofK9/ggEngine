#include "Raven.h"
#include "CVGame.h"
#include "Simon.h"
Raven::Raven(CVGame * cvGame, SpriteInfo * image) : TweenEnemyBase(cvGame,image,16,16,0,4,200)
{
	CreateAnimation("idle",0,0,false);
	CreateAnimation("move", 1, 3, true);
	SetMoveX(40);
	SetSpeed(1.5);
	this->body->SetActive(false);
	this->timeOutBetweenCheck = 1000;
	this->simonDetectRange = 150;
}

Raven::~Raven()
{
}

void Raven::Active()
{
	EnemyBase::Active();
	this->allowToDetectSimon = true;
	this->body->SetActive(false);
	this->body->immoveable = true;
	if (this->currentTimeOut != nullptr) {
		this->currentTimeOut->Stop();
		this->currentTimeOut = nullptr;
	}
	if (this->currentTween != nullptr) {
		this->currentTween->Stop();
		this->currentTween = nullptr;
	}

}
void Raven::Update()
{
	EnemyBase::Update();
}
void Raven::OnSimonEnterRange(Simon * simon, bool isLeft)
{
	this->allowToDetectSimon = false;
	PlayAnimation("move");
	CheckAndFly();
}
void Raven::CheckAndFly()
{
	auto simonPosition = this->simon->position;
	bool isLeft = simonPosition.x < this->position.x;
	bool isFlyHorizontal = (simonPosition.y > this->GetTop() && simonPosition.y < this->GetBottom()) || this->simon->position.y < this->GetTop();
	if (isFlyHorizontal) FlyHorizontal(isLeft);
	else {
		AddTween(isLeft);
	}
	ChangeFacingDirection(isLeft);

}
void Raven::FlyHorizontal(bool isLeft)
{
	int modifier = 1;
	if (isLeft) modifier = -1;
	this->body->SetActive(true);
	this->body->immoveable = false;
	this->body->velocity.x = modifier*speed;
}
void Raven::AddTween(bool isLeft)
{
	Vector simonPosition = this->cvGame->simon->position;
	Vector moveTo = simonPosition;
	int modifier = 1;
	if (isLeft) modifier = -1;
	moveTo.x = this->position.x + modifier*moveX;
	this->currentTween = this->cvGame->add->MoveTo(this, moveTo, round(moveX / speed) * DEFAULT_MS_PER_FRAME_FOR_ANIMATION, Easing::easeInQuad, Easing::easeOutQuad)->SetOnFinish([this]() {
		this->currentTween = nullptr;
		this->currentTimeOut = this->game->add->TimeOut(timeOutBetweenCheck, [this]() {
			CheckAndFly();
			this->currentTimeOut = nullptr;
		})->Start();
	})->Start();
}
