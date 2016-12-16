#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVGame;
class SimonGroup : public Group {
public:
	SimonGroup(CVGame *cvGame);
	~SimonGroup();

	void CheckCollisionTo(std::list<GameObject*> staticGoList);
private:
};