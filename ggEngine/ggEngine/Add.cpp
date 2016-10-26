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
namespace ggEngine{
	Add::Add(World *world, Cache *cache, TweenManager *tweenManager, DrawManager *drawManager, Camera *camera){
		this->cache = cache;
		this->drawManager = drawManager;
		this->device = drawManager->GetDevice();
		this->world = world;
		this->tweenManager = tweenManager;
		this->camera = camera;
	}
	Sprite* Add::Sprite(double x, double y, std::string textureKey, ggEngine::Group *group){
		SpriteInfo* inf = this->cache->GetSpriteInfo(textureKey);
		ggEngine::Sprite *sprite = new ggEngine::Sprite(this->drawManager, inf);
		sprite->SetParentObject(group);
		sprite->SetPosition(x, y);
		group->AddDrawObjectToList(sprite);
		return sprite;
	}
	SpriteAnimation* Add::SpriteAnimation(double x, double y, std::string textureKey, int frameWidth, int frameHeight, ggEngine::Group * group, int defaultFrame, int numberOfFrame , int msPerFrame)
	{
		SpriteInfo* inf = this->cache->GetSpriteInfo(textureKey);
		ggEngine::SpriteAnimation *spriteAnimation = new ggEngine::SpriteAnimation(this->drawManager, inf, frameWidth, frameHeight, defaultFrame, numberOfFrame, msPerFrame);
		spriteAnimation->SetParentObject(group);
		spriteAnimation->SetPosition(x, y);
		group->AddDrawObjectToList(spriteAnimation);
		return spriteAnimation;
	}
	Group* Add::Group(){
		ggEngine::Group *gr = new ggEngine::Group();
		world->AddGroup(gr);
		return gr;
	}
	TileMap * Add::TileMap(std::string tileMapJsonPath)
	{
		ggEngine::TileMap *tileMap = new ggEngine::TileMap(this->camera, this->drawManager, this->cache);
		tileMap->BuildTree(tileMapJsonPath);
		world->AddGroup(tileMap);
		return tileMap;
	}
	Text* Add::Text(double x, double y, std::string fontKey, double width, double height, std::string text, Style style, ggEngine::Group  *group)
	{
		Font* font = this->cache->GetFont(fontKey);
		ggEngine::Text *textObject = new ggEngine::Text(this->drawManager,font, x, y, width, height, text, style);
		textObject->SetParentObject(group);
		group->AddDrawObjectToList(textObject);
		return textObject;
	}

	Audio* Add::Audio(std::string audioKey){
		return new ggEngine::Audio();
	}
	ggEngine::Tween * Add::Tween(float & val, double end, double duration, std::function<double(int,double,double,int)> easingFunction)
	{
		ggEngine::Tween* tween = new ggEngine::Tween(this->tweenManager, val, end, duration, easingFunction);
		this->tweenManager->AddTween(tween);
		return tween;
	}
	//ggEngine::Tween * Add::Tween(double init, double end, double duration, std::function<void(double)> update, std::function<double(double)> easingFunction)
	//{
	//	return NULL;
	//	/*ggEngine::Tween* tween = new ggEngine::Tween(this->tweenManager, init, end, duration, update, easingFunction);
	//	return tween;*/
	//}
}