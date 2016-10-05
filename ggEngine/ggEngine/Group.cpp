#include "Group.h"
#include "DrawManager.h"
#include "Sprite.h"
namespace ggEngine{
	Group::Group(DrawManager *drawManager){
		this->drawManager = drawManager;
	}
	Group::~Group(){
		//TO DO remove all child group and all child sprite here
	}
	void Group::Destroy(){
		GameObject::Destroy();
	}
	void Group::Update()
	{
		if (this->update != nullptr) update();
	}
	void Group::AddDrawObjectToList(DrawObject* drawObject){
		drawList.push_back(drawObject);
	}
	void Group::Reset(){

		for (std::list<DrawObject*>::const_iterator it = drawList.begin(); it != drawList.end(); it++)
		{
			delete *it;
		}
		drawList.clear();
	}
}