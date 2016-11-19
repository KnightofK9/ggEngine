#include "State.h"
#include "Group.h"
#include "Add.h"
#include "Preload.h"
#include "DrawManager.h"
#include "World.h"
#include "Game.h"
namespace ggEngine {
	State::State(Game *game) {
		this->drawManager = game->GetDrawManager();
		this->game = game;
		this->world = game->world;
		Load();
	}
	State::~State() {
		delete add;
		delete preload;
	}
	void State::Start()
	{
		Init();
		Preload();
		Create();
	}
	void State::Load()
	{
		this->add = new ggEngine::Add(game->world, game->cache, game->tweenManager, game->GetDrawManager(), game->camera, game->physics, game->timeBasedEventManager);
		this->preload = new ggEngine::Preload(game->cache);

	}
	void State::Destroy() {

	}
}