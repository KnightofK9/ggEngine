#pragma once
#include <ggEngine.h>
#include "CVObject.h"
using namespace ggEngine;
class CVGame;
class TileBase :public SingleTile,public CVObject {
public:
	TileBase(CVGame *cvGame, TileMap *tileMap, SpriteInfo *image);
	virtual ~TileBase();
};