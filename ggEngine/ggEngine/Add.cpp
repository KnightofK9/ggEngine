#include "Add.h"
#include "Group.h"
#include "Sprite.h"
#include "DrawManager.h"
namespace ggEngine{
	Add::Add(DrawManager *drawManager){
		this->drawManager = drawManager;		
	}
	Sprite* Add::Sprite(float x, float y, std::string textureKey, int frameName, ggEngine::Group *group){
		Texture* texture = this->drawManager->GetTexture(textureKey);
		ggEngine::Sprite *sprite = new ggEngine::Sprite(this->drawManager->GetDevice(), texture);
		group->AddSpriteToList(sprite);
		return sprite;
	}
	Group* Add::Group(){
		ggEngine::Group *gr = new ggEngine::Group(NULL);
		return gr;
	}
}