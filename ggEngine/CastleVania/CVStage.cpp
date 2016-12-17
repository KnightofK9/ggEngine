#include "CVStage.h"

CVStage::CVStage(std::string json)
{
	Json stageJson(json);
	this->stageNumber = stageJson["number"].GetInt();
	for (auto &block : stageJson["blockList"].GetArray()) {
		CVBlock* cvBlock = new CVBlock(Json::GetCharArrayFromValue(block));
		this->blockList.push_back(cvBlock);
	}

	this->primaryBlock = blockList[0];
}

CVStage::CVStage(std::vector<CVBlock*> blockList, int stageNumber)
{
	this->blockList = blockList;
	this->stageNumber = stageNumber;
	this->primaryBlock = blockList[0];
}

CVStage::~CVStage()
{
	for (auto block : this->blockList) {
		delete block;
	}
}
