#pragma once
#include <ggEngine.h>
#include "CVBlock.h"
using namespace ggEngine;
class CVStage : public GGObject {
public:
	CVStage(std::string json);
	CVStage(std::vector<CVBlock*> blockList, int stageNumber);
	~CVStage();
private:
	std::vector<CVBlock*> blockList;
	CVBlock* primaryBlock = nullptr;
	int stageNumber;
};