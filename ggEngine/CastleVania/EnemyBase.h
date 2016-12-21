#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
using namespace ggEngine;
class Simon;
class EnemyBase : public CVSpriteAnimation {
public:
	EnemyBase(CVGame *cvGame, SpriteInfo *image, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~EnemyBase();

	virtual void OnSimonContact(Simon *simon, ColliderArg e);
	virtual void Active();
	virtual bool OnCheckingCollide(ColliderArg e);
	virtual void Update();
protected:
	bool isLeft;
	void ChangeFacingDirection(bool isLeft);
	unsigned int health;
	unsigned int maxHealth;
};