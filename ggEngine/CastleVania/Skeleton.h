#pragma once
#include "ShootingEnemyBase.h"
class Skeleton : public ShootingEnemyBase {
public:
	Skeleton(CVGame *cvGame, SpriteInfo* image);
	virtual ~Skeleton();
	void Active() override;
	void Update() override;
private:
	bool OnCheckingCollide(ColliderArg e) override;
	void OnSimonEnterRange(Simon* simon, bool isLeft);
	Timer movingTimer;
	Timer stopTimer;
	void ResetStoppingTime();
	void ResetMovingTime();

	double moveSpeed;
	double simonKeepingDistance;
	int randomFireIntevalMin;
	int randomFireIntevalMax;
	int randomMoveTimeMin;
	int randomMoveTimeMax;
	int randomStopMoveTimeMin;
	int randomStopMoveTimeMax;
	int movingTimerInterval;
	int stoppingTimerInterval;
	bool isPausing;
	bool isMoving;
	int globalModifier;
};