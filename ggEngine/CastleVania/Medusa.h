#pragma once
#include "TweenEnemyBase.h"
class Medusa : public TweenEnemyBase {
public:
	Medusa(CVGame* cvGame, SpriteInfo *spriteInfo);
	virtual ~Medusa();

	void RunLeft() override;
	void RunRight() override;
	void Update() override;
private:
	double simonDetectRange = 50.0f;
};