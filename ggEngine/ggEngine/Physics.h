#pragma once
#include "GGObject.h"
#include <list>
namespace ggEngine {
	class Game;
	class Sprite;
	class Body;
	class Physics:public GGObject {
	public:
		Physics(Game *game);
		~Physics();
		void UpdatePhysics();
		void EnablePhysics(Sprite *sprite);
	private:
		Game *game;
		std::list<Body*> bodyList;
	};
}