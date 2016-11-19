#include "CVState.h"
#include "CVAdd.h"
CVState::CVState(Game * game):State(game)
{
}

CVState::CVState(Game * game, Json state):State(game)
{

}

CVState::~CVState()
{
}

void CVState::Load()
{
	this->add = new CVAdd(game->world, game->cache, game->tweenManager, game->GetDrawManager(), game->camera, game->physics, game->timeBasedEventManager);
	this->preload = new ggEngine::Preload(game->cache);
}

void CVState::LoadJson(Json state)
{

}

