#pragma once
#include "EnemyBase.h"
class TweenEnemyBase : public EnemyBase {
public:
	TweenEnemyBase(CVGame *cvGame, SpriteInfo *spriteInfo, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~TweenEnemyBase();

	virtual void RunLeft();
	virtual void RunRight();
	void Update() override;
	void SetMoveY(double moveY);
	void SetMoveX(double moveX);
	void SetSpeed(double speed);
	double GetSpeed();
	virtual void SetPosition(Vector position) override;
protected:
	Vector startPosition;
	double moveY = 50;
	double moveX = 0;
	double speed = 0.25;
	bool isMoving = false;
};