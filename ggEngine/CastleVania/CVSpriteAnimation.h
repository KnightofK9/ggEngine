#pragma once
#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVGame;
class CVSpriteAnimation : public SpriteAnimation {
public:
	CVSpriteAnimation(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~CVSpriteAnimation();
protected:
	CVGame *cvGame;
};