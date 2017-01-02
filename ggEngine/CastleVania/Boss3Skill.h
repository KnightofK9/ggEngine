#pragma once
#include "EnemySkillBase.h"
class Boss3Skill : public EnemySkillBase {
public:
	Boss3Skill(CVGame *cvGame, SpriteInfo *image);
	~Boss3Skill();

private:
	// Inherited via EnemySkillBase
	EnemySkillBase* GetBulletInstance() override;
};