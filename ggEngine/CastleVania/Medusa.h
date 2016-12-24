#pragma once
#include "ShootingEnemyBase.h"
class Simon;
class Medusa : public ShootingEnemyBase {
public:
	Medusa(CVGame *cvGame, SpriteInfo *image);
	virtual ~Medusa();

	void Update() override;
	void Active() override;


private:
	void MoveTo(Vector position);
	bool isMoving;
	void Awake();
	void OnSimonEnterRange(Simon* simon, bool isLeft) override;
	Simon *simon = nullptr;
	const int timeOutToAwake = 2000;
	TweenBase *currentTween = nullptr;
	double moveX;
	double moveY;
	double moveSpeed;
	Timer moveTimer;
	bool isAwake;
	int moveInterval = 1000;
	Vector lastSimonPosition;
	const double randomMinX = 10;
	const double randomMaxX = 60;
};