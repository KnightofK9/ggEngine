#pragma once
#include <ggEngine.h>
#include "ItemBase.h"
using namespace ggEngine;
class MiniHealth : public ItemBase {
public:
	MiniHealth(CVGame *cvgame, SpriteInfo *image);
	~MiniHealth();
};