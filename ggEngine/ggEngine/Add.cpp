#include "Add.h"
#include "Group.h"
#include "Cache.h"
#include "DrawManager.h"
#include "SpriteAnimation.h"
namespace ggEngine{
	Add::Add(Cache *cache, LPDIRECT3DDEVICE9 device, std::list<ggEngine::Group*> *groupList){
		this->cache = cache;
		this->groupList = groupList;
		this->device = device;
	}
	Sprite* Add::Sprite(float x, float y, std::string textureKey, int frameName, ggEngine::Group *group){
		Texture* texture = this->cache->GetTexture(textureKey);
		ggEngine::Sprite *sprite = new ggEngine::Sprite(this->device, texture);
		sprite->SetPosition(x, y);
		group->AddSpriteToList(sprite);
		return sprite;
	}
	SpriteAnimation* Add::SpriteAnimation(std::string textureKey, int frameWidth, int frameHeight, ggEngine::Group * group, int defaultFrame, int numberOfFrame)
	{
		Texture* texture = this->cache->GetTexture(textureKey);
		ggEngine::SpriteAnimation *spriteAnimation = new ggEngine::SpriteAnimation(this->device, texture, frameWidth, frameHeight, defaultFrame, numberOfFrame);
		return spriteAnimation;
	}
	Group* Add::Group(){
		ggEngine::Group *gr = new ggEngine::Group(NULL);
		this->groupList->push_back(gr);
		return gr;
	}
}