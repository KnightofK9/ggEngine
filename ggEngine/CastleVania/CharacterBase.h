#pragma once
#include <ggEngine.h>
#include "CVObject.h"
#include "CVSpriteAnimation.h"
using namespace ggEngine;
class CVGame;
class CharacterBase : public CVSpriteAnimation, public CVObject {
public:
	CharacterBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~CharacterBase();
};