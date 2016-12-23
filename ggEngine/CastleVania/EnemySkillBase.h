#pragma once
#include "CVSpriteAnimation.h"
class EnemySkillBase : public CVSpriteAnimation {
public:
	EnemySkillBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~EnemySkillBase();

	void Active();
protected:
	virtual void OnSimonContact(ColliderArg e);
	virtual bool OnCheckingCollide(ColliderArg e);
};