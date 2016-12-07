#pragma once
#include <ggEngine.h>
#include "TileBrick.h"
using namespace ggEngine;
class CVGame;
class StaticTileManager : public GGObject {
public:
	StaticTileManager(CVGame *cvGame);
	virtual ~StaticTileManager();
	TileBrick* AddTileBrick(double x, double y, Group *group = nullptr);
private:
	Preload* preload = nullptr;
	Add* add = nullptr;
	Cache* cache = nullptr;
	CVGame* cvGame = nullptr;
};