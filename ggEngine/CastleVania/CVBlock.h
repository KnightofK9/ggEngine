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
	int stageIndex;
	int blockIndex;
private:
	std::string name;
	SimonGroundingType simonGroundingType;
	SimonLadderType simonLadderType;
};