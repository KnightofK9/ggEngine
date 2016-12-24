#pragma once
#include "EnemySkillBase.h"
class EnemySkillFire : public EnemySkillBase {
public:
	EnemySkillFire(CVGame *cvGame, SpriteInfo * image);
	virtual ~EnemySkillFire();
	// Inherited via EnemySkillBase
	void Fire(bool isLeft, Vector position) override;
protected:
};