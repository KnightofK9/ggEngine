#pragma once
#include "TweenEnemyBase.h"
class Simon;
class Medusa : public TweenEnemyBase {
public:
	Medusa(CVGame *cvGame, SpriteInfo *image);
	virtual ~Medusa();

	void Update() override;
	void Active() override;


private:
	void Awake();
	void RunLeft() override;
	void RunRight() override;
	void OnSimonEnterRange(Simon* simon, bool isLeft) override;
	Simon *simon = nullptr;
	const int timeOutToAwake = 2000;
};