#include "Group.h"
#include "DrawManager.h"
#include "Sprite.h"
namespace ggEngine{
	Group::Group(DrawManager *drawManager){
		this->drawManager = drawManager;
	}
	Group::~Group(){
		Destroy();
	}
	void Group::Destroy(){

	}
	void Group::Update()
	{
		if (this->update != nullptr) update();
	}
	void Group::AddSpriteToList(Sprite* sprite){
		drawList.push_back(sprite);
	}
}