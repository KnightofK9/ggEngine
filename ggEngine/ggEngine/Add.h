#pragma once
#include "GGObject.h"
#include <string>
#include <list>
#include <d3d9.h>
namespace ggEngine{
	class Sprite;
	class Group;
	class Cache;
	class Add:public GGObject  {
	public:
		Add(Cache *Cache, LPDIRECT3DDEVICE9 device, std::list<ggEngine::Group*> *groupList);
		Sprite* Sprite(float x, float y, std::string textureKey, int frameName, Group *group);
		Group* Group();
	private:
		std::list<ggEngine::Group*> *groupList;
		Cache *cache;
		LPDIRECT3DDEVICE9 device;
	};
}