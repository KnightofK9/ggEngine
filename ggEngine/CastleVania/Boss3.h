#pragma once
#include "WalkingEnemyBase.h"
class Boss3 : public WalkingEnemyBase {
public:
	Boss3(CVGame *cvGame, SpriteInfo* image, bool isPrimaryBoss);
	~Boss3();
private:
	bool isPrimaryBoss;
};