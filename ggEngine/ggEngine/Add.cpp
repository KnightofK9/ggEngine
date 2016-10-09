#include "Add.h"
#include "Group.h"
#include "Cache.h"
#include "DrawManager.h"
#include "SpriteAnimation.h"
#include "World.h"
namespace ggEngine{
	Add::Add(World *world, Cache *cache, DrawManager *drawManager, std::list<ggEngine::Group*> *groupList){
		this->cache = cache;
		this->drawManager = drawManager;
		this->device = drawManager->GetDevice();
		this->world = world;
	}
	Sprite* Add::Sprite(float x, float y, std::string textureKey, ggEngine::Group *group){
		SpriteInfo* inf = this->cache->GetSpriteInfo(textureKey);
		ggEngine::Sprite *sprite = new ggEngine::Sprite(this->drawManager, inf);
		sprite->SetParentObject(group);
		sprite->SetPosition(x, y);
		group->AddDrawObjectToList(sprite);
		return sprite;
	}
	SpriteAnimation* Add::SpriteAnimation(float x, float y, std::string textureKey, int frameWidth, int frameHeight, ggEngine::Group * group, int defaultFrame, int numberOfFrame)
	{
		SpriteInfo* inf = this->cache->GetSpriteInfo(textureKey);
		ggEngine::SpriteAnimation *spriteAnimation = new ggEngine::SpriteAnimation(this->drawManager, inf, frameWidth, frameHeight, defaultFrame, numberOfFrame);
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
	Text* Add::Text(float x, float y, std::string fontKey, float width, float height, std::string text, Style style, ggEngine::Group  *group)
	{
		Font* font = this->cache->GetFont(fontKey);
		ggEngine::Text *textObject = new ggEngine::Text(this->drawManager,font, x, y, width, height, text, style);
		textObject->SetParentObject(group);
		group->AddDrawObjectToList(textObject);
		return textObject;
	}
}