#pragma once
#include "GGObject.h"
#include <string>
#include <list>
#include <d3d9.h>
#include "Text.h"
namespace ggEngine{
	class Sprite;
	class Group;
	class SpriteAnimation;
	class Cache;
	class Add:public GGObject  {
	public:
		Add(Cache *Cache, LPDIRECT3DDEVICE9 device, std::list<ggEngine::Group*> *groupList);
		Sprite* Sprite(float x, float y, std::string textureKey, int frameName, Group *group);
		SpriteAnimation* SpriteAnimation(float x, float y, std::string textureKey ,int frameWidth, int frameHeight, Group *group, int defaultFrame = 0, int numberOfFrame = 0);
		Group* Group();
		//Here how a text is added, it must be added to a group created via add->Group()
		Text* Text(float x, float y, float width, float height, std::string text, Style style, ggEngine::Group *group);
	private:
		std::list<ggEngine::Group*> *groupList;
		Cache *cache;
		LPDIRECT3DDEVICE9 device;
	};
}