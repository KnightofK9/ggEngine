#pragma once
#include "TweenEnemyBase.h"
class BatEnemy : public TweenEnemyBase {
public:
	BatEnemy(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~BatEnemy();
	void RunLeft() override;
	void RunRight() override;
	void Update() override;

	void OnSimonEnterRange(Simon* simon, bool isLeft) override;
private:
	void AddTween(bool isLeft);
};