#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class CVGame;
class Heart : public ItemBase {
public:
	Heart(CVGame *cvgame, SpriteInfo *image);
	virtual ~Heart();

	void Active() override;
	void OnSimonContact(Simon *simon, ColliderArg e) override;
	//void SetPosition(Vector position, bool isRefresh = false) override;
private:
	Vector startPosition;
	//const int healthGain = 1;
	TimeBasedEventInfo *loopMovingSin = nullptr;
	const int point = 1;
	double moveX;
	double moveY;
};