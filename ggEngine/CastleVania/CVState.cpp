#include "CVState.h"
CVState::CVState(Game * game):State(game)
{
}

CVState::CVState(Game * game, Json state):State(game)
{
	this->json = state.GetCharArray;
}

CVState::~CVState()
{
}

void CVState::Init()
{
}

void CVState::Preload()
{
}

void CVState::Create()
{
}

void CVState::Update()
{
}

void CVState::PreRender()
{
}

void CVState::Render()
{
}

void CVState::Pause()
{
}

void CVState::Resume()
{
}

void CVState::ShutDown()
{
}

void CVState::Load()
{
	this->add = new CVAdd(game->world, game->cache, game->tweenManager, game->GetDrawManager(), game->camera, game->physics, game->timeBasedEventManager);
	this->preload = new CVPreload(game->cache);
}


