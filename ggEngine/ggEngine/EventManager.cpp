#include "EventManager.h"
#include "Game.h"
#include "GameObject.h"
#include "Events.h"
ggEngine::EventManager::EventManager(Game * game)
{
	this->game = game;
}

ggEngine::EventManager::~EventManager()
{
}

void ggEngine::EventManager::Destroy()
{
}

void ggEngine::EventManager::EnableInput(GameObject *go)
{

	if (go->events == NULL){
		go->events = new Events(game, go);
	}
}
