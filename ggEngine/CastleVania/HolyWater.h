#pragma once
#include <ggEngine.h>
#include "WeaponBase.h"

using namespace ggEngine;
class HolyWater : public WeaponBase
{
public:
	HolyWater(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~HolyWater();
};

