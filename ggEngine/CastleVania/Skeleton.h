#pragma once
#include "ShootingEnemyBase.h"
class Skeleton : public ShootingEnemyBase {
public:
	Skeleton(CVGame *cvGame, SpriteInfo* image);
	virtual ~Skeleton();
	void Active() override;
	void Update() override;
private:
	void OnBrickContact(TileBrick *tileBrick, ColliderArg e) override;
	bool OnCheckingCollide(ColliderArg e) override;
	void OnSimonEnterRange(Simon* simon, bool isLeft);
	Timer movingTimer;
	Timer stopTimer;
	void ResetMovingTime();

	double moveSpeed;
	double jumpForce;
	double simonKeepingDistance;
	int randomFireIntevalMin;
	int randomFireIntevalMax;
	int randomMoveTimeMin;
	int randomMoveTimeMax;
	int movingTimerInterval;
	bool isMoving;
	int globalModifier;
};