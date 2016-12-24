#pragma once
#include <ggEngine.h>
#include "StaticTile.h"
using namespace ggEngine;
class CVGame;
class TileBrick : public StaticTile {
public:
	TileBrick(CVGame *cvGame, SpriteInfo *info);
	~TileBrick();
	bool IsOnEdge(GameObject* movingObject);
};