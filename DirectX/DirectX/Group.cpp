#include "Group.h"

Group::Group() :GameObject(0, 0)
{
	spriteList = new List<Sprite>();
}

Group::~Group()
{
	delete spriteList;
}

Sprite * Group::addSprite(std::string spriteName)
{
	return nullptr;
}

