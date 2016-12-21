#pragma once
#include "TweenEnemyBase.h"
class AI6 : public TweenEnemyBase {
public:
	AI6(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~AI6();

	void RunLeft() override;
	void RunRight() override;
	void Update() override;
	void Active() override;
	bool isLeft;

	void OnBrickContact(TileBrick* brick, ColliderArg e) override;
private:
	bool isRunning;
};