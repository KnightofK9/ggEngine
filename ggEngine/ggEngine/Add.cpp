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
#include "ScreenGroup.h"
#include "TimeBasedEventInfo.h"
#include "TimeBasedEventManager.h"
#include "Grid.h"
#include "EventManager.h"
#include "Game.h"
#include "Tile.h"
#include "TileSet.h"
#include "MultiTween.h"
int (WINAPIV * __vsnprintf)(char *, size_t, const char*, va_list) = _vsnprintf;

namespace ggEngine{
	Add::Add(Game *game){
		this->game = game;
		this->cache = game->cache;
		this->drawManager = game->GetDrawManager();
		this->device = drawManager->GetDevice();
		this->world = game->world;
		this->tweenManager = game->tweenManager;
		this->camera = game->camera;
		this->physics = game->physics;
		this->timeBasedEventManager = game->timeBasedEventManager;
		this->eventManager = game->eventManager;
	}
	Tile * Add::Tile(std::string tileSetKey, int tileId)
	{
		SpriteInfo* inf = this->cache->GetTileMap(tileSetKey)->GetTileSetAt(tileId);
		ggEngine::Tile *tile = new ggEngine::Tile(this->game, inf);
		return tile;
	}
	Sprite* Add::Sprite(double x, double y, std::string textureKey, ggEngine::Group *group){
		SpriteInfo* inf = this->cache->GetSpriteInfo(textureKey);
		ggEngine::Sprite *sprite = new ggEngine::Sprite(this->game, inf);
		sprite->SetPosition(x, y);
		group->AddDrawObjectToList(sprite);
		return sprite;
	}
	ggEngine::Sprite * Add::Sprite(double x, double y, std::string tileSetKey, unsigned int tileId, ggEngine::Group * group)
	{
		SpriteInfo* inf = this->cache->GetTileMap(tileSetKey)->GetTileSetAt(tileId);
		ggEngine::Sprite *sprite = new ggEngine::Sprite(this->game, inf);
		sprite->SetPosition(x, y);
		group->AddDrawObjectToList(sprite);
		return sprite;
	}
	Grid * Add::Grid(double x, double y, int cellWidth, int cellHeight, int width, int height, ggEngine::Group * group)
	{
		ggEngine::Grid* grid = new ggEngine::Grid(this->game);
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
		ggEngine::SpriteAnimation *spriteAnimation = new ggEngine::SpriteAnimation(this->game, inf, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame);
		spriteAnimation->SetPosition(x, y);
		group->AddDrawObjectToList(spriteAnimation);
		return spriteAnimation;
	}
	Group* Add::Group(){
		ggEngine::Group *gr = new ggEngine::Group(this->game);
		world->AddGroup(gr);
		return gr;
	}
	ScreenGroup * Add::ScreenGroup()
	{
		ggEngine::ScreenGroup *gr = new ggEngine::ScreenGroup(this->game);
		world->AddGroup(gr);
		return gr;
	}
	TileMap * Add::TileMap(const char* jsonChar,ggEngine::Group *group)
	{
		ggEngine::TileMap *tileMap = new ggEngine::TileMap(this->game);
		tileMap->BuildTileMap(jsonChar);
		group->AddGroup(tileMap);
		return tileMap;
	}
	Text* Add::Text(double x, double y, std::string fontKey, double width, double height, std::string text, Style style, ggEngine::Group  *group)
	{
		Font* font = this->cache->GetFont(fontKey);
		ggEngine::Text *textObject = new ggEngine::Text(this->game,font, x, y, width, height, text, style);
		group->AddDrawObjectToList(textObject);
		return textObject;
	}

	Audio* Add::Audio(std::string audioKey){
		AudioInfo *audioInfo = this->cache->GetAudioInfo(audioKey);
		ggEngine::Audio *audio = new ggEngine::Audio(this->game, audioInfo);
		return audio;
	}
	ggEngine::TweenBase * Add::Tween(float & val, double end, double duration, std::function<double(int,double,double,int)> easingFunction)
	{
		ggEngine::Tween* tween = new ggEngine::Tween(this->tweenManager, val, end, duration, easingFunction);
		this->tweenManager->AddTween(tween);
		return tween;
	}
	ggEngine::TweenBase * Add::Tween(double init, double end, double duration, std::function<double(int, double, double, int)> easingFunction,  std::function<void(double)> update)
	{
		ggEngine::Tween* tween = new ggEngine::Tween(this->tweenManager, init, end, duration, update, easingFunction);
		this->tweenManager->AddTween(tween);
		return tween;
	}
	ggEngine::MultiTween * Add::MultiTween(std::list<TweenBase*> tweenList)
	{
		for (TweenBase *tween : tweenList) {
			this->tweenManager->RemoveTween(tween);
		}
		ggEngine::MultiTween * tween = new ggEngine::MultiTween(tweenList,this->tweenManager);
		this->tweenManager->AddTween(tween);
		return tween;
	}
	ggEngine::TweenBase * Add::MoveBy(GameObject * go, Vector distance, double duration, std::function<double(int, double, double, int)> easingFunction)
	{
		Vector startPosition = go->position;
		TweenBase* moveX = this->Tween(go->position.x, distance.x + startPosition.x, duration, easingFunction);
		TweenBase* moveY = this->Tween(go->position.y, distance.y + startPosition.y, duration, easingFunction);
		TweenBase* multiTween = this->MultiTween({ moveX,moveY });
		return multiTween;
	}
	ggEngine::TweenBase * Add::MoveTo(GameObject * go, Vector newPosition, double duration, std::function<double(int, double, double, int)> easingFunction)
	{
		TweenBase* moveX = this->Tween(go->position.x, newPosition.x, duration, easingFunction);
		TweenBase* moveY = this->Tween(go->position.y, newPosition.y, duration, easingFunction);
		TweenBase* multiTween = this->MultiTween({ moveX,moveY });
		return multiTween;
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
	GameObject * Add::AddObjectBaseOnType(std::string type)
	{
		return nullptr;
	}
}