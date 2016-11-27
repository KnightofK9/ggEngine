#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
using namespace ggEngine;
class EnemyBase : public CVSpriteAnimation {
public:
	EnemyBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~EnemyBase();
};