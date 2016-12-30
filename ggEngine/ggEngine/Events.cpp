#include "Events.h"
#include "Game.h"
#include "EventManager.h"
ggEngine::Events::Events(Game * game, GameObject * go)
{
	this->game = game;
	this->go = go;
	this->enable = true;
	this->wasInCamera = false;
}

ggEngine::Events::~Events()
{
	this->game->eventManager->RemoveEventFromAllManager(this->go);
}


