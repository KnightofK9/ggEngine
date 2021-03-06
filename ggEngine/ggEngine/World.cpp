#include "World.h"
#include "DrawManager.h"
#include "Game.h"
namespace ggEngine {
	World::World(Game * game, double width, double height) : Group(game)
	{
		this->name = "World";
		SetScale(1, 1);
		SetPosition(0, 0);
		SetAnchor(0, 0);
		this->worldPosition = Vector(0, 0);
		this->worldScale = Vector(1, 1);
		SetOpacityAffectByParent(false);
		this->width = width;
		this->height = height;
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
	void World::UpdateWorldPosition()
	{
	}

}
