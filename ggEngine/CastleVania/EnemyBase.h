#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
class TileBrick;
using namespace ggEngine;
class Simon;
class EnemyBase : public CVSpriteAnimation {
public:
	EnemyBase(CVGame *cvGame, SpriteInfo *image,int frameWidth,int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~EnemyBase();

	virtual void OnSimonContact(ColliderArg e);
	virtual void Active();
	virtual bool OnCheckingCollide(ColliderArg e);
	virtual void Update();
	virtual void RunLeft();
	virtual void RunRight();
	virtual void OnSimonEnterRange(Simon* simon,bool isLeft);
	virtual void OnSimonOutOfRange(Simon* simon, bool isLeft);
	virtual void OnBrickContact(TileBrick *tileBrick, ColliderArg e);

protected:
	bool isLeft;
	void ChangeFacingDirection(bool isLeft);
	unsigned int health;
	unsigned int maxHealth;
	double simonDetectRange = 50.0f;
	bool allowToDetectSimon = false;
	bool detectX = true;
	bool detectY = true;

	int damage;
	int point;
};