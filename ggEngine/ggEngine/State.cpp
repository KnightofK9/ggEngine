#include "State.h"
#include "Group.h"
#include "Add.h"
#include "Preload.h"
#include "DrawManager.h"
#include "World.h"
#include "Game.h"
namespace ggEngine {
	State::State(Game *game,bool isLoadAutomatic) {
		this->drawManager = game->GetDrawManager();
		this->game = game;
		this->world = game->world;
		if(isLoadAutomatic) Load();
	}
	State::~State() {
		if (add != nullptr) {
			delete add;
			add = nullptr;
		}
		if (preload != nullptr) {
			delete preload;
			preload = nullptr;
		}
	}
	void State::Start()
	{
		Init();
		Preload();
		Create();
	}
	void State::Load()
	{
		this->add = new ggEngine::Add(game);
		this->preload = new ggEngine::Preload(game->cache);

	}

}