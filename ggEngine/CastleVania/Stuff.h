#pragma once
#include <ggEngine.h>
#include "ItemBaseAnim.h"

using namespace ggEngine;
class Stuff : public ItemBaseAnim {
public:
	Stuff(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~Stuff();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};