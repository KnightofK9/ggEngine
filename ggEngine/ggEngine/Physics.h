#pragma once
#include "GGObject.h"
#include <list>
#include "ColliderArg.h"
#include "GameObject.h"
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
		void CheckBound(GameObject *go1, GameObject *go2);
	private:
		Game *game;
		std::list<Body*> bodyList;
	};
}