#pragma once
#include "TweenEnemyBase.h"
class BatEnemy : public TweenEnemyBase {
public:
	BatEnemy(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~BatEnemy();
	void RunLeft() override;
	void RunRight() override;
	void Update() override;
private:
	void AddTween(bool isLeft);
	double simonDetectRange = 50.0f;
};