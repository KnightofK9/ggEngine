#include "Events.h"

ggEngine::Events::Events(Game * game, GameObject * go)
{
	this->game = game;
	this->go = go;
	enable = true;
}

ggEngine::Events::~Events()
{
}

void ggEngine::Events::Destroy()
{
}
