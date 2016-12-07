#pragma once
#include <ggEngine.h>
#include "TypeEnum.h"
#include "CVSprite.h"
using namespace ggEngine;
class CVGame;
class StaticTile :public CVSprite {
public:
	StaticTile(CVGame *cvGame, SpriteInfo *image);
	virtual ~StaticTile();
protected:
	
};