#pragma once
#include <ggEngine.h>
#include "TileBase.h"
using namespace ggEngine;
class StaticTile :public TileBase {
public:
	StaticTile(Physics *physics, DrawManager *drawManager, TileMap *tileMap, SpriteInfo *image);
	~StaticTile();
};