#pragma once
#include "GGObject.h"
#include <string>
#include <list>
#include <d3d9.h>
#include "Text.h"
#include <boost/function.hpp>
namespace ggEngine{
	class Tween;
	class TweenManager;
	class Font;
	class Sprite;
	class Group;
	class SpriteAnimation;
	class Cache;
	class DrawManager;
	class World;
	class Add:public GGObject  {
	public:
		Add(World *world,Cache *Cache,TweenManager *tweenManager, DrawManager *drawManager, std::list<ggEngine::Group*> *groupList);
		Sprite* Sprite(double x, double y, std::string textureKey, Group *group);
		SpriteAnimation* SpriteAnimation(double x, double y, std::string textureKey ,int frameWidth, int frameHeight, Group *group, int defaultFrame = 0, int numberOfFrame = 0);
		Group* Group();
		Text* Text(double x, double y, std::string fontKey , double width, double height, std::string text, Style style, ggEngine::Group *group);
		ggEngine::Tween* Tween(double &val, double end, double duration, boost::function<double(double)> easingFunction);
		ggEngine::Tween* Tween(double init, double end, double duration, std::function<void(double)> update, boost::function<double(double)> easingFunction);

	private:
		TweenManager *tweenManager;
		Cache *cache;
		DrawManager *drawManager;
		LPDIRECT3DDEVICE9 device;
		World *world;
	};
}