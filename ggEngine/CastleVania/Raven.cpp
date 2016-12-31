#include "Raven.h"
#include "CVGame.h"
#include "Simon.h"
Raven::Raven(CVGame * cvGame, SpriteInfo * image) : TweenEnemyBase(cvGame,image,16,16,0,4,200)
{
	CreateAnimation("idle",0,0,false);
	CreateAnimation("move", 1, 3, true);
	this->body->SetActive(false);
}

Raven::~Raven()
{
}

void Raven::Active()
{
	EnemyBase::Active();
}

void Raven::Update()
{
	EnemyBase::Update();
}
void Raven::AddTween(bool isLeft)
{
	Vector simon = this->cvGame->simon->position;
	Vector moveTo = simon;
	int modifier = 1;
	if (isLeft) modifier = -1;
	moveTo.x = this->position.x + modifier*moveX;
	this->currentTween = this->cvGame->add->MoveTo(this, moveTo, round(moveX / speed) * DEFAULT_MS_PER_FRAME_FOR_ANIMATION, Easing::easeInQuad, Easing::easeOutQuad)->SetOnFinish([=]() {
		this->currentTween = nullptr;
		this->body->immoveable = false;
		this->body->velocity.x = modifier*speed;
	})->Start();
}
