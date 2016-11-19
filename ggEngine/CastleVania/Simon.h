#pragma once
#include <ggEngine.h>
#include "CharacterBase.h"
using namespace ggEngine;
class Simon :public CharacterBase {
public:
	Simon(DrawManager *drawManager, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~Simon();
};