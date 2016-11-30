#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
using namespace ggEngine;
class Simon;
class EnemyBase : public CVSpriteAnimation {
public:
	EnemyBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~EnemyBase();

	virtual void CheckCollisionToSimon(Simon *simon);
	virtual void OnSimonContact(Simon *simon, ColliderArg e);
	virtual void Active();
protected:
	unsigned int health;
	unsigned int maxHealth;
};