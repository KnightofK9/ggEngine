#include "State.h"
#include "Group.h"
#include "Add.h"
#include "Preload.h"
#include "DrawManager.h"
#include "World.h"
#include "Game.h"
namespace ggEngine{
	State::State(Game *game){
		this->drawManager = game->GetDrawManager();
		this->game = game;
		this->world = game->world;
		add = new ggEngine::Add( game->world ,game->cache,game->tweenManager , game->GetDrawManager(), &this->groupList);
		preload = new ggEngine::Preload(game->cache);
	}
	State::~State(){
		delete add;
		delete preload;
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