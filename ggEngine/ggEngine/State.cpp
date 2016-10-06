#include "State.h"
#include "Group.h"
#include "Add.h"
#include "Preload.h"
#include "DrawManager.h"
#include "Game.h"
#include "World.h"
namespace ggEngine{
	State::State(Game *game){
		this->drawManager = game->GetDrawManager();
		this->game = game;
		add = new ggEngine::Add( game->world ,game->cache, game->GetDrawManager(), &this->groupList);
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