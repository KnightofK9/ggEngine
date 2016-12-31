#pragma once
#include "TweenEnemyBase.h"
class Raven : public TweenEnemyBase {
public:
	Raven(CVGame *cvGame, SpriteInfo *image);
	virtual ~Raven();

	virtual void Active() override;
	virtual void Update() override;
private:
	void AddTween(bool isLeft);
	TweenBase* currentTween = nullptr;
};