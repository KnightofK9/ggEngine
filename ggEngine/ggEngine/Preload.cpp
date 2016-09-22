#include "Preload.h"
#include "Sprite.h"
#include "Group.h"
namespace ggEngine{
	Preload::Preload(DrawManager *drawManager){
		this->drawManager = drawManager;
	}
	Sprite* Preload::Sprite(std::string textureKey, std::string texturePath){
		return NULL;
	}
}