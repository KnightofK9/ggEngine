#pragma once
#include <ggEngine.h>
#include "Simon.h"
using namespace ggEngine;
class CVBlock : public Rect {
public:
	CVBlock(std::string json);
	~CVBlock();
private:
	std::string name;
	int stageNumber;
	int levelNumber;
	Vector simonSpawnPosition;
	Vector cameraSpawnPosition;
	SimonGroundingType simonGroundingType;
	SimonLadderType simonLadderType;
};