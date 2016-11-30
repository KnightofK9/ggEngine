#pragma once
#include <ggEngine.h>
#include "TileBase.h"
using namespace ggEngine;
class CVGame;
class StaticTile :public TileBase {
public:
	StaticTile(CVGame *cvGame, TileMap *tileMap, SpriteInfo *image);
	~StaticTile();
};