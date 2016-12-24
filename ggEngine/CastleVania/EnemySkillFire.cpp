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

EnemySkillBase * EnemySkillFire::GetBulletInstance()
{
	auto go = new EnemySkillFire(this->cvGame, this->image);
	AddBulletToGroup(go);
	return go;
}

