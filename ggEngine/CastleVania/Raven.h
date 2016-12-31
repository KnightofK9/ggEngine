#pragma once
#include "TweenEnemyBase.h"
class Raven : public TweenEnemyBase {
public:
	Raven(CVGame *cvGame, SpriteInfo *image);
	virtual ~Raven();

	virtual void Active() override;
	virtual void Update() override;
private:
	void OnSimonEnterRange(Simon* simon, bool isLeft) override;
	void CheckAndFly();
	void FlyHorizontal(bool isLeft);
	void AddTween(bool isLeft);
	double timeOutBetweenCheck;
	TweenBase* currentTween = nullptr;
	TimeBasedEventInfo* currentTimeOut = nullptr;
};