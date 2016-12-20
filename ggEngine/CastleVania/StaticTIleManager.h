#pragma once
#include <ggEngine.h>
#include "TileBrick.h"
#include "ManagerBase.h"
#include "TileLadder.h"
#include "TypeEnum.h"
#include "Door.h"
using namespace ggEngine;
class CVGame;
class StaticTileManager : public ManagerBase {
public:
	StaticTileManager(CVGame *cvGame);
	virtual ~StaticTileManager();
	void PreloadAll();
	Door* AddDoor(double x, double y, Group* group = nullptr);
	TileBrick* AddTileBrick(double x, double y,double width, double height, Group *group = nullptr);
	TileLadder* AddTileLadder(double x, double y, ObjectType ladderType, Group *group = nullptr);
private:
};