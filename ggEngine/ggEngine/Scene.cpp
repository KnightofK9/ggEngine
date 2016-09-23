#include "State.h"
#include "Group.h"
#include "Add.h"
#include "Preload.h"
#include "DrawManager.h"
namespace ggEngine{
	State::State(DrawManager *drawManager){
		this->drawManager = drawManager;
	}
	State::~State(){
		Destroy();
	}
	void State::Start()
	{
		Init();
	}
	void State::Destroy(){

	}
}