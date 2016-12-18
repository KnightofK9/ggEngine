#include "CVStage.h"

CVStage::CVStage(std::string json)
{
	Json stageJson(json);
	this->stageIndex = stageJson["number"].GetInt();
	int blockIndex = 0;
	for (auto &block : stageJson["blockList"].GetArray()) {
		CVBlock* cvBlock = new CVBlock(Json::GetCharArrayFromValue(block));
		cvBlock->stageIndex = this->stageIndex;
		cvBlock->blockIndex = blockIndex;
		blockIndex++;
		this->blockList.push_back(cvBlock);
	}

	this->primaryBlock = blockList[0];
}

CVStage::CVStage(std::vector<CVBlock*> blockList, int stageNumber)
{
	this->blockList = blockList;
	this->stageIndex = stageNumber;
	this->primaryBlock = blockList[0];
}

CVStage::~CVStage()
{
	for (auto block : this->blockList) {
		delete block;
	}
}
