
#include "World.h"


	ggEngine::World::World()
	{
	}

	ggEngine::World::~World()
	{
	}

	void ggEngine::World::Reset()
	{
		for (std::list<Group*>::const_iterator it = groupList.begin(); it != groupList.end(); it++)
		{
			delete *it;
		}
		groupList.clear();
	}
