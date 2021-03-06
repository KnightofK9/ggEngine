#pragma once
#include "EnemyBase.h"
#include "StaticTile.h"
using namespace ggEngine;
class WalkingEnemyBase : public EnemyBase {
public:
	WalkingEnemyBase(CVGame *cvGame, SpriteInfo *spriteInfo,int frameWidth,int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~WalkingEnemyBase();
	
	virtual bool OnCheckingCollide(ColliderArg e) override;
	virtual void RunLeft();
	virtual void RunRight();
	virtual void Update() override;
	virtual void Active() override;
protected:
	StaticTile* steppingTile = nullptr;
	void SetMoveForce(double moveForce);
	double moveForce = 5.0f;
	bool isRunning = false;
};