#pragma once
#include "Sprite.h"
#include "List.h"
#include <iostream>
class Group: public GameObject {
public:
	Group();
	~Group();
	Sprite* addSprite(std::string spriteName);
private:
	List<Sprite> *spriteList;
};