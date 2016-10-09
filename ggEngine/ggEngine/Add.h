#pragma once
#include "GGObject.h"
#include <string>
#include <list>
#include <d3d9.h>
#include "Text.h"
namespace ggEngine{
	class Font;
	class Sprite;
	class Group;
	class SpriteAnimation;
	class Cache;
	class DrawManager;
	class World;
	class Add:public GGObject  {
	public:
		Add(World *world,Cache *Cache, DrawManager *drawManager, std::list<ggEngine::Group*> *groupList);
		Sprite* Sprite(float x, float y, std::string textureKey, Group *group);
		SpriteAnimation* SpriteAnimation(float x, float y, std::string textureKey ,int frameWidth, int frameHeight, Group *group, int defaultFrame = 0, int numberOfFrame = 0);
		Group* Group();
		Text* Text(float x, float y, std::string fontKey , float width, float height, std::string text, Style style, ggEngine::Group *group);
	private:
		Cache *cache;
		DrawManager *drawManager;
		LPDIRECT3DDEVICE9 device;
		World *world;
	};
}