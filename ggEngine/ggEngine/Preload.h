#pragma once
#include "GGObject.h"
#include <string>
namespace ggEngine{
	class Sprite;
	class Group;
	class Cache;
	class Preload :public GGObject  {
	public:
		Preload(Cache *cache);
		void Texture(std::string textureKey, std::string texturePath);
	private:
		Cache *cache;
	};
}