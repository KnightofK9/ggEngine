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
		Physics(Game *game,PhysicsMode physicsMode);
		~Physics();
		void UpdatePhysics();
		void EnablePhysics(Sprite *sprite);
		void CheckBound(GameObject *go1, GameObject *go2);
		void Reset();
	private:
		void CheckBoundAABB(GameObject *go1, GameObject *go2);
		void CheckBoundSweptAABB(GameObject *go1, GameObject *go2);
		PhysicsMode physicsMode;
		Game *game;
		std::list<Body*> bodyList;
	};
}