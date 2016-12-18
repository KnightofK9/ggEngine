#pragma once
#include <ggEngine.h>
#include "Simon.h"
using namespace ggEngine;
class CVBlock : public Rect {
public:
	CVBlock(std::string json);
	~CVBlock();
	Vector simonSpawnPosition;
	Vector cameraSpawnPosition;
private:
	std::string name;
	int stageNumber;
	int levelNumber;
	SimonGroundingType simonGroundingType;
	SimonLadderType simonLadderType;
};