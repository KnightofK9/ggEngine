#pragma once
#include "WalkingEnemyBase.h"
class AxeKnight : public WalkingEnemyBase {
public:
	AxeKnight(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~AxeKnight();

	void RunLeft();
	void RunRight();
private:
};