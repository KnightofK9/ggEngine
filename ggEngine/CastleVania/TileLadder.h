#pragma once
#include <ggEngine.h>
#include "StaticTile.h"
using namespace ggEngine;
class CVGame;
class TileLadder : public StaticTile {
public:
	TileLadder(CVGame *cvGame, SpriteInfo *info);
	~TileLadder();
};