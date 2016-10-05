#include "Add.h"
#include "Group.h"
#include "Cache.h"
#include "DrawManager.h"
#include "SpriteAnimation.h"
namespace ggEngine{
	Add::Add(Cache *cache, DrawManager *drawManager, std::list<ggEngine::Group*> *groupList){
		this->cache = cache;
		this->groupList = groupList;
		this->drawManager = drawManager;
		this->device = drawManager->GetDevice();
	}
	Sprite* Add::Sprite(float x, float y, std::string textureKey, int frameName, ggEngine::Group *group){
		Texture* texture = this->cache->GetTexture(textureKey);
		ggEngine::Sprite *sprite = new ggEngine::Sprite(this->drawManager, texture);
		sprite->SetPosition(x, y);
		group->AddDrawObjectToList(sprite);
		return sprite;
	}
	SpriteAnimation* Add::SpriteAnimation(float x, float y, std::string textureKey, int frameWidth, int frameHeight, ggEngine::Group * group, int defaultFrame, int numberOfFrame)
	{
		Texture* texture = this->cache->GetTexture(textureKey);
		ggEngine::SpriteAnimation *spriteAnimation = new ggEngine::SpriteAnimation(this->drawManager, texture, frameWidth, frameHeight, defaultFrame, numberOfFrame);
		spriteAnimation->SetPosition(x, y);
		group->AddDrawObjectToList(spriteAnimation);
		return spriteAnimation;
	}
	Group* Add::Group(){
		ggEngine::Group *gr = new ggEngine::Group(NULL);
		this->groupList->push_back(gr);
		return gr;
	}
	Text* Add::Text(float x, float y,float width, float height, std::string text, Style style, ggEngine::Group  *group)
	{
		ggEngine::Text *textObject = new ggEngine::Text(this->drawManager, x, y, width, height, text, style);
		group->AddDrawObjectToList(textObject);
		return textObject;
	}
}