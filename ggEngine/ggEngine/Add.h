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
		Sprite* Sprite(double x, double y, std::string textureKey, Group *group);
		SpriteAnimation* SpriteAnimation(double x, double y, std::string textureKey ,int frameWidth, int frameHeight, Group *group, int defaultFrame = 0, int numberOfFrame = 0);
		Group* Group();
		Text* Text(double x, double y, std::string fontKey , double width, double height, std::string text, Style style, ggEngine::Group *group);
	private:
		Cache *cache;
		DrawManager *drawManager;
		LPDIRECT3DDEVICE9 device;
		World *world;
	};
}