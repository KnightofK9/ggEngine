#pragma once
#include "ShootingEnemyBase.h"
class Simon;
class Medusa : public ShootingEnemyBase {
public:
	Medusa(CVGame *cvGame, SpriteInfo *image);
	virtual ~Medusa();

	void Update() override;
	void Active() override;
	//void Destroy() override;
	void Kill() override;
	int LoseHealth(int health) override;

private:
	TimeBasedEventInfo *awakingTimeOut;
	void MoveToNextPosition();
	void MoveTo(Vector position);
	bool isMoving;
	void Awake();
	void OnSimonEnterRange(Simon* simon, bool isLeft) override;
	TweenBase *currentTween = nullptr;
	double moveX;
	double moveY;
	double moveSpeed;
	Timer moveTimer;
	bool isAwake;

	double pauseTimer;
	bool isPausingMoving;
	Vector lastSimonPosition;
	int moveInterval;
	double randomMinX;
	double randomMaxX;
	int minRandomPause;
	int maxRandomPause;
	int timeOutToAwake;
};