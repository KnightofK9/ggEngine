#include "Raven.h"

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
