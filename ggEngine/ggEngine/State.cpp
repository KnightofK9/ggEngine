#include "State.h"
#include "Group.h"
#include "Add.h"
#include "Preload.h"
#include "DrawManager.h"
#include "Game.h"
namespace ggEngine{
	State::State(Game *game){
		this->drawManager = game->GetDrawManager();
		add = new ggEngine::Add(game->cache, &game->GetD3DManager()->getDevice(), &this->groupList);
		preload = new ggEngine::Preload(game->cache);
	}
	State::~State(){
		Destroy();
	}
	void State::Start()
	{
		Init();
		Preload();
		Create();
	}
	void State::Destroy(){

	}
}