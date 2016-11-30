#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVSprite : public Sprite {
public:
	CVSprite(Game *game, SpriteInfo *image);
	~CVSprite();
};