#include "World.h"
namespace ggEngine {
	World::World()
	{
		SetScale(1, 1);
		SetPosition(0, 0);
		this->worldPosition = Vector(0, 0);
		this->worldScale = Vector(1, 1);
	}
	World::~World()
	{
	}
	void World::Reset()
	{
		for (std::list<Group*>::const_iterator it = groupList.begin(); it != groupList.end(); it++)
		{
			delete *it;
		}
		groupList.clear();
	}
}
