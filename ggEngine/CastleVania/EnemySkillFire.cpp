#include "EnemySkillFire.h"
#include "CVGame.h"
#include "Simon.h"
#include "CVMap.h"
EnemySkillFire::EnemySkillFire(CVGame * cvGame, SpriteInfo * image) : EnemySkillBase(cvGame,image,7,6)
{
}

EnemySkillFire::~EnemySkillFire()
{
}

void EnemySkillFire::Fire(bool isLeft, Vector position)
{
	int modifier = 1;
	if (isLeft) modifier = -1;
	EnemySkillFire* fire = this->AddSkill<EnemySkillFire>(position);
	fire->body->velocity.x = modifier*this->fireSpeed;
	fire->Active();
}
