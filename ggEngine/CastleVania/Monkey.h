#pragma once
#include "TweenEnemyBase.h"
class Monkey : public TweenEnemyBase {
public:
	Monkey(CVGame *cvGame, SpriteInfo *image);
	virtual ~Monkey();

	virtual void Active() override;
	virtual void Update() override;
private:
};