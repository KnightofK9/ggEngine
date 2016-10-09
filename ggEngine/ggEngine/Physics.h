#pragma once
#include "GGObject.h"
#include <list>
#include "ColliderArg.h"
#include "GameObject.h"
namespace ggEngine {
	extern float timeEntrySAABB; // For using Swept AABB

	class Game;
	class Sprite;
	class Body;
	class Physics:public GGObject {
	public:
		Physics(Game *game,PhysicsMode physicsMode);
		~Physics();
		void UpdatePhysics();
		void EnablePhysics(Sprite *sprite);
		void Reset();

	private:
		PhysicsMode physicsMode;
		Game *game;
		std::list<Body*> bodyList;

	};
}