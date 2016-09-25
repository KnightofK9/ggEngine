#include "Physics.h"
#include "Body.h"
#include "Game.h"
#include "Sprite.h"
namespace ggEngine {
	Physics::Physics(Game * game)
	{
		this->game = game;
	}
	Physics::~Physics()
	{
		//TO DO remove all body here
	}
	void Physics::UpdatePhysics()
	{
		for (std::list<Body*>::iterator it = this->bodyList.begin();it != this->bodyList.end();) {
			if ((*it)->IsAlive()) {
				(*it)->Update();
				++it;
			}
			else {
				std::list<Body*>::iterator tempIt = it;
				++it;
				delete (*tempIt);
				bodyList.erase(tempIt);
			}
		}
	}
	void Physics::EnablePhysics(Sprite * sprite)
	{
		Body* body = new Body(game, sprite);
		bodyList.push_back(body);
		sprite->SetBody(body);
	}
}