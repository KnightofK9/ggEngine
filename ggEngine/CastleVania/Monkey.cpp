#include "Monkey.h"

Monkey::Monkey(CVGame * cvGame, SpriteInfo * image) : TweenEnemyBase(cvGame, image, 16, 16, 0, 2, 200)
{
	CreateAnimation("move", 0, 1, true);
	this->body->SetActive(false);
}

Monkey::~Monkey()
{
}

void Monkey::Active()
{
	EnemyBase::Active();
}

void Monkey::Update()
{
	EnemyBase::Update();
}
