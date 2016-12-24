#pragma once
#include "WalkingEnemyBase.h"
class AxeKnight : public WalkingEnemyBase {
public:
	AxeKnight(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~AxeKnight();

	void RunLeft();
	void RunRight();

private:
	//const int damage = 2;
	//const int health = 2;
	//const int point = 400;
};