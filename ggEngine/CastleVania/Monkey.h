#pragma once
#include "WalkingEnemyBase.h"
class Monkey : public EnemyBase {
public:
	Monkey(CVGame *cvGame, SpriteInfo *image);
	virtual ~Monkey();

	void Active() override;
	void Update() override;
private:
	bool OnCheckingCollide(ColliderArg e) override;
	void Jump(bool isLeft, bool isHighJump);

	double jumpForce;
	double highJumpForce;
	Vector jumpDirection;
	Vector highJumpDirection;
	bool isGrounding;
	double distanceUntilToJumpHigh;
};