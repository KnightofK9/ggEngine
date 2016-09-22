#include "Preload.h"
#include "Group.h"
#include "Sprite.h"
#include "DrawManager.h"
namespace ggEngine{
	Preload::Preload(DrawManager *drawManager){
		this->drawManager = drawManager;
	}
	void Preload::Sprite(std::string textureKey, std::string texturePath){
		this->drawManager->CreateTexture(textureKey, texturePath);
	}
}