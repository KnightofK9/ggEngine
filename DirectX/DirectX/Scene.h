#pragma once
#include "RevertList.h"
#include "Group.h"
class Scene {
public:
	Scene();
	~Scene();
	Group* addGroup();

private:
	RevertList<Group> *groupList;
};