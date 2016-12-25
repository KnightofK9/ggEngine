#pragma once
#include "EnemySkillBase.h"
class SkeletonSkill : public EnemySkillBase {
public:
	SkeletonSkill(CVGame *cvGame, SpriteInfo* image);
	virtual ~SkeletonSkill();
	void Active() override;
	void Fire(bool isLeft, Vector position) override;
private:
	// Inherited via EnemySkillBase
	EnemySkillBase* GetBulletInstance() override;
};