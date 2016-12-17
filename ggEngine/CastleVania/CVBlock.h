#pragma once
#include <ggEngine.h>
#include "Simon.h"
using namespace ggEngine;
class CVBlock : public Rect {
public:
	CVBlock(double left, double top, double right, double bottom, std::string name);
	~CVBlock();
private:
	std::string name;
	int stageNumber;
	int levelNumber;
	Vector simonSpawnPosition;
	SimonGroundingType simonGroundingType;
	SimonLadderType simonLadderType;
};