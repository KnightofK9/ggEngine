#pragma once
#include <ggEngine.h>
#include "CVObject.h"
using namespace ggEngine;
class TileBase :public SingleTile,public CVObject {
public:
	TileBase( DrawManager *drawManager, TileMap *tileMap, SpriteInfo *image);
	~TileBase();
};