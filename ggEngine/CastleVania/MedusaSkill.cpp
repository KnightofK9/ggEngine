#include "MedusaSkill.h"

MedusaSkill::MedusaSkill(CVGame * cvGame, SpriteInfo * image) : EnemySkillBase(cvGame,image,17,10,0,2,200)
{
	CreateAnimation("move", 0, 1,true);
}

MedusaSkill::~MedusaSkill()
{
}
