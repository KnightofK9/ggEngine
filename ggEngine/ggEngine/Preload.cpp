#include "Preload.h"
#include "Group.h"
#include "Sprite.h"
#include "Cache.h"
namespace ggEngine{
	Preload::Preload(Cache *cache){
		this->cache = cache;
	}
	void Preload::Sprite(std::string textureKey, std::string texturePath){
		this->cache->CreateTexture(textureKey, texturePath);
	}
}