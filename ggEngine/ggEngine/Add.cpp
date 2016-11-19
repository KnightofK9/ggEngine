#include "Add.h"
#include "Group.h"
#include "Cache.h"
#include "DrawManager.h"
#include "SpriteAnimation.h"
#include "World.h"
#include "Tween.h"
#include "TweenManager.h"
#include "Audio.h"
#include "TileMap.h"
#include "Camera.h"
#include "Physics.h"
#include "TimeBasedEventInfo.h"
#include "TimeBasedEventManager.h"
#include "Grid.h"
#include "EventManager.h"
namespace ggEngine{
	Add::Add(World *world, Cache *cache, TweenManager *tweenManager, DrawManager *drawManager, Camera *camera,  Physics* physics, TimeBasedEventManager *timeBasedEventManager, EventManager *eventManager){
		this->cache = cache;
		this->drawManager = drawManager;
		this->device = drawManager->GetDevice();
		this->world = world;
		this->tweenManager = tweenManager;
		this->camera = camera;
		this->physics = physics;
		this->timeBasedEventManager = timeBasedEventManager;
		this->eventManager = eventManager;
	}
	Sprite* Add::Sprite(double x, double y, std::string textureKey, ggEngine::Group *group){
		SpriteInfo* inf = this->cache->GetSpriteInfo(textureKey);
		ggEngine::Sprite *sprite = new ggEngine::Sprite(this->drawManager, inf);
		sprite->SetPosition(x, y);
		group->AddDrawObjectToList(sprite);
		return sprite;
	}
	Grid * Add::Grid(double x, double y, int cellWidth, int cellHeight, int width, int height, ggEngine::Group * group)
	{
		ggEngine::Grid* grid = new ggEngine::Grid(this->camera,this->drawManager);
		grid->SetCellWidth(cellWidth);
		grid->SetCellHeight(cellHeight);
		grid->SetWidth(width);
		grid->SetHeight(height);
		group->AddDrawObjectToList(grid);
		return grid;
	}
	SpriteAnimation* Add::SpriteAnimation(double x, double y, std::string textureKey, int frameWidth, int frameHeight, ggEngine::Group * group, int defaultFrame, int numberOfFrame , int msPerFrame)
	{
		SpriteInfo* inf = this->cache->GetSpriteInfo(textureKey);
		ggEngine::SpriteAnimation *spriteAnimation = new ggEngine::SpriteAnimation(this->drawManager, inf, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame);
		spriteAnimation->SetPosition(x, y);
		group->AddDrawObjectToList(spriteAnimation);
		return spriteAnimation;
	}
	Group* Add::Group(){
		ggEngine::Group *gr = new ggEngine::Group();
		world->AddGroup(gr);
		return gr;
	}
	TileMap * Add::TileMap(std::string tileMapJson,bool isLocation)
	{
		ggEngine::TileMap *tileMap = new ggEngine::TileMap(this->camera, this->drawManager,this->cache,this->physics);
		tileMap->BuildTree(tileMapJson, isLocation);
		this->physics->AddTileMap(tileMap);
		world->AddGroup(tileMap);
		return tileMap;
	}
	Text* Add::Text(double x, double y, std::string fontKey, double width, double height, std::string text, Style style, ggEngine::Group  *group)
	{
		Font* font = this->cache->GetFont(fontKey);
		ggEngine::Text *textObject = new ggEngine::Text(this->drawManager,font, x, y, width, height, text, style);
		group->AddDrawObjectToList(textObject);
		return textObject;
	}

	Audio* Add::Audio(std::string audioKey){
		return new ggEngine::Audio(audioKey);
	}
	ggEngine::Tween * Add::Tween(float & val, double end, double duration, std::function<double(int,double,double,int)> easingFunction)
	{
		ggEngine::Tween* tween = new ggEngine::Tween(this->tweenManager, val, end, duration, easingFunction);
		this->tweenManager->AddTween(tween);
		return tween;
	}
	ggEngine::Tween * Add::Tween(double init, double end, double duration, std::function<double(int, double, double, int)> easingFunction,  std::function<void(double)> update)
	{
		ggEngine::Tween* tween = new ggEngine::Tween(this->tweenManager, init, end, duration, update, easingFunction);
		this->tweenManager->AddTween(tween);
		return tween;
	}
	TimeBasedEventInfo * Add::TimeOut(unsigned int delay, std::function<void(void)> function)
	{
		TimeBasedEventInfo *e = new TimeBasedEventInfo();
		e->type = TimeBasedEvent_Single;
		e->delay = delay;
		e->function = function;
		this->timeBasedEventManager->AddEvent(e);
		return e;
	}
	TimeBasedEventInfo * Add::LoopInfinity(unsigned int delay, std::function<void(void)> function)
	{
		TimeBasedEventInfo *e = new TimeBasedEventInfo();
		e->type = TimeBasedEvent_LoopInfinity;
		e->delay = delay;
		e->function = function;
		this->timeBasedEventManager->AddEvent(e);
		return e;
	}
	TimeBasedEventInfo * Add::Loop(unsigned int delay, unsigned int numberOfLoops, std::function<void(void)> function)
	{
		TimeBasedEventInfo *e = new TimeBasedEventInfo();
		e->type = TimeBasedEvent_Loop;
		e->delay = delay;
		e->function = function;
		e->numberOfLoops = numberOfLoops;
		this->timeBasedEventManager->AddEvent(e);
		return e;
	}
}