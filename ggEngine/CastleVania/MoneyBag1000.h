#pragma once
#include <ggEngine.h>
#include "ItemBaseAnim.h"

using namespace ggEngine;
class MoneyBag1000 : public ItemBaseAnim {
public:
	MoneyBag1000(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~MoneyBag1000();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
	int money = 1000;
};