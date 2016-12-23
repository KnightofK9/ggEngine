#include "BonePillar.h"

BonePillar::BonePillar(CVGame * cvGame, SpriteInfo * spriteInfo) : EnemyBase(cvGame,spriteInfo,16,32)
{
	this->body->SetActive(false);
	this->SetAnchor(0.5, 0);
}

BonePillar::~BonePillar()
{
}

void BonePillar::Update()
{
}
