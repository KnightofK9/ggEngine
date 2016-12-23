#include "BonePillar.h"

BonePillar::BonePillar(CVGame * cvGame, SpriteInfo * spriteInfo) : EnemyBase(cvGame,spriteInfo,16,32)
{
	this->body->SetActive(false);
}

BonePillar::~BonePillar()
{
}
