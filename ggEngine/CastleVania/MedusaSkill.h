#pragma once
#include "EnemySkillBase.h"
class MedusaSkill : public EnemySkillBase {
public:
	MedusaSkill(CVGame* cvGame, SpriteInfo* image);
	virtual ~MedusaSkill();
	void Active() override;
private:
	// Inherited via EnemySkillBase
	EnemySkillBase* GetBulletInstance() override;
	bool OnCheckingCollide(ColliderArg e) override;
	void ChangeFacingDirection(bool isLeft) override;
};