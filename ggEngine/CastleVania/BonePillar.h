#pragma once
#include "EnemyBase.h"
class BonePillar : public EnemyBase {
public:
	BonePillar(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~BonePillar();
};