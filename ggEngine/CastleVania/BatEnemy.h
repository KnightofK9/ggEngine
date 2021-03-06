#pragma once
#include "TweenEnemyBase.h"
class BatEnemy : public TweenEnemyBase {
public:
	BatEnemy(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~BatEnemy();
	void RunLeft() override;
	void RunRight() override;
	void Update() override;
	void Destroy() override;

	void OnSimonEnterRange(Simon* simon, bool isLeft) override;
	void Active() override;
private:
	void AddTween(bool isLeft);
	TweenBase * currentTween = nullptr;
	//const int damage = 2;
	//const int health = 1;
	//const int point = 200;
};