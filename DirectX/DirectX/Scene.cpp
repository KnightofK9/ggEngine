#include "Scene.h"

Scene::Scene()
{
	groupList = new RevertList<Group>();
}

Scene::~Scene()
{
	delete groupList;
}

Group * Scene::addGroup()
{
	return nullptr;
}
