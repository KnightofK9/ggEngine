#pragma once
#include "EnemySkillBase.h"
class EnemySkillFire : public EnemySkillBase {
public:
	EnemySkillFire(CVGame *cvGame, SpriteInfo * image);
	virtual ~EnemySkillFire();
private:
	// Inherited via EnemySkillBase
	EnemySkillBase* GetBulletInstance() override;
};