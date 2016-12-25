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
	void Active() override;
private:
	void AddTween(bool isLeft);
	TweenBase* currentTween = nullptr;
	double minX = 10;
	double minY = -10;

	//const int damage = 2;
	//const int health = 2;
	//const int point = 300;
};