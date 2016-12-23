#pragma once
#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVGame;
class CVSpriteAnimation : public SpriteAnimation {
public:
	CVSpriteAnimation(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~CVSpriteAnimation();

	virtual TimeBasedEventInfo* FlickeringAnimation(int delay, int duration);	//visible and invisible
	virtual TimeBasedEventInfo* FlickeringChangeColorAnimation(int delay, int duration);
	virtual TimeBasedEventInfo* FlickeringChangeColorAnimationInfinity(int delay);

protected:
	CVGame *cvGame;

private:
	int rgbKey = 1;	//1: r, 2: g, 3:b, 4: v
	TimeBasedEventInfo* flickeringChangeColorAnim = nullptr;
};