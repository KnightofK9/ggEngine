#pragma once
#include "GGObject.h"
#include <string>
#include <list>
#include <d3d9.h>
#include "Text.h"

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
	class Audio;
	class Camera;
	class TileMap;
	class Grid;
	class ScreenGroup;
	class Physics;
	class TimeBasedEventManager;
	class TimeBasedEventInfo;
	class EventManager;
	class Game;
	class Tile;
	class Add:public GGObject  {
	public:
		Add(Game *game);
		Tile* Tile(std::string tileSetKey, int tileId);
		Sprite* Sprite(double x, double y, std::string textureKey, Group *group);
		ggEngine::Sprite* Sprite(double x, double y, std::string tileSetKey, unsigned int tileId, ggEngine::Group *group);
		Grid *Grid(double x, double y,int cellWidth, int cellHeight, int width, int height, Group *group);
		SpriteAnimation* SpriteAnimation(double x, double y, std::string textureKey ,int frameWidth, int frameHeight, Group *group, int defaultFrame = 0, int numberOfFrame = 0, int msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
		Group* Group();
		ScreenGroup *ScreenGroup();
		TileMap* TileMap(const char* jsonChar, ggEngine::Group *group);
		Text* Text(double x, double y, std::string fontKey , double width, double height, std::string text, Style style, ggEngine::Group *group);
		Audio* Audio(std::string audioKey);
		ggEngine::Tween* Tween(float &val, double end, double duration, std::function<double(int, double, double, int)> easingFunction);
		ggEngine::Tween* Tween(double init, double end, double duration, std::function<double(int, double, double, int)> easingFunction, std::function<void(double)> update);
		TimeBasedEventInfo* TimeOut(unsigned int delay , std::function<void(void)> function);
		TimeBasedEventInfo* LoopInfinity(unsigned int delay, std::function<void(void)> function);
		TimeBasedEventInfo* Loop(unsigned int delay, unsigned int numberOfLoops, std::function<void(void)> function);
		GameObject* AddObjectBaseOnType(std::string type);
	protected:
		Physics *physics;
		TweenManager *tweenManager;
		Cache *cache;
		Camera *camera;
		DrawManager *drawManager;
		LPDIRECT3DDEVICE9 device;
		World *world;
		TimeBasedEventManager *timeBasedEventManager;
		EventManager *eventManager;
		Game *game;
	};
}