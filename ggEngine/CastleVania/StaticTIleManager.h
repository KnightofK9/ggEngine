#pragma once
#include <ggEngine.h>
#include "TileBrick.h"
#include "ManagerBase.h"
using namespace ggEngine;
class CVGame;
class StaticTileManager : public ManagerBase {
public:
	StaticTileManager(CVGame *cvGame);
	virtual ~StaticTileManager();
	TileBrick* AddTileBrick(double x, double y, Group *group = nullptr);
private:
};