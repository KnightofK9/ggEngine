#include "Add.h"
#include "Sprite.h"
#include "Group.h"
namespace ggEngine{
	Add::Add(DrawManager *drawManager){
		this->drawManager = drawManager;		
	}
	Sprite* Add::Sprite(std::string textureKey){
		return NULL;
	}
	Group* Add::Group(){
		ggEngine::Group *gr = new ggEngine::Group(NULL);
		return gr;
	}
}