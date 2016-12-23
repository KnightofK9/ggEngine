#pragma once
#include "TweenEnemyBase.h"
class Ghost : public TweenEnemyBase {
public:
	Ghost(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~Ghost();
	void RunLeft() override;
	void RunRight() override;
	void Update() override;

	void OnSimonEnterRange(Simon* simon, bool isLeft) override;
private:
	void AddTween(bool isLeft);
};