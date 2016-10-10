#pragma once
#include "GGObject.h"
#include <list>
#include "ColliderArg.h"
#include "GameObject.h"
#include "Box.h"
namespace ggEngine {
	extern double timeEntrySAABB; // For using Swept AABB

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
		static Box CreateSweptBroadPhaseBox(Box b);
		static bool AABBCheck(Box b1, Box b2);
	private:
		PhysicsMode physicsMode;
		Game *game;
		std::list<Body*> bodyList;

	};
}