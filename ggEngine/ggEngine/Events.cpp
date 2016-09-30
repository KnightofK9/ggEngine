#include "Events.h"

ggEngine::Events::Events(Game * game, GameObject * go)
{
	this->game = game;
	this->go = go;
}

ggEngine::Events::~Events()
{
}

void ggEngine::Events::Destroy()
{
}
