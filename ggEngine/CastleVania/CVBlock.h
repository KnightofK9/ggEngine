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
	void AddObjectToRevivedList(GameObject* go);
	void ClearRevivedList();
	void Reset();
private:
	std::string name;
	std::list<GameObject*> revivedList;
	SimonGroundingType simonGroundingType;
	SimonLadderType simonLadderType;
};