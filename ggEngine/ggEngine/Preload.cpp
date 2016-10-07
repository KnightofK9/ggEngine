#include "Preload.h"
#include "Group.h"
#include "Sprite.h"
#include "Cache.h"
namespace ggEngine{
	Preload::Preload(Cache *cache){
		this->cache = cache;
	}
	void Preload::Texture(std::string textureKey, std::string texturePath){
		this->cache->CreateTexture(textureKey, texturePath);
		
	}
	void Preload::Atlas(std::string atlasName, std::string atlasPath, std::string atlasDefPath, AtlasDefType type)
	{
		switch (type) {
		case AtlasDefTypeXML:
			this->cache->CreateTextureFromAtlasXML(atlasName, atlasPath, atlasDefPath);
			break;
		case AtlasDefTypeJSON:
			break;
		}
	}
}