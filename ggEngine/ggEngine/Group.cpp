#include "Group.h"
namespace ggEngine{
	Group::Group(DrawManager *drawManager){
		this->drawManager = drawManager;
	}
	Group::~Group(){
		Destroy();
	}
	void Group::Destroy(){

	}
}