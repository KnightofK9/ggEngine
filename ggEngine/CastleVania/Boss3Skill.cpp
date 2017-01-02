#include "Boss3Skill.h"

Boss3Skill::Boss3Skill(CVGame * cvGame, SpriteInfo * image) : EnemySkillBase(cvGame, image, 16, 9)
{
	CreateAnimation("move", 0, 1, true);
	PlayAnimation("move");
}

Boss3Skill::~Boss3Skill()
{
}

EnemySkillBase * Boss3Skill::GetBulletInstance()
{
	auto go = new Boss3Skill(this->cvGame, this->image);
	AddBulletToGroup(go);
	return go;
}
