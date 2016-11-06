#pragma once
#include "GGObject.h"
#include <list>
#include "ColliderArg.h"
#include "GameObject.h"
#include "Box.h"
#include <vector>
#include "Rect.h"
namespace ggEngine {
	class TileMap;
	class Game;
	class Sprite;
	class Body;
	class Physics:public GGObject {
	public:
		Physics(Game *game,PhysicsMode physicsMode);
		~Physics();
		void UpdatePhysics();
		void EnablePhysics(GameObject * gameObject);
		void AttachBodyTo(GameObject *gameObject);
		void Reset();
		void AddTileMap(TileMap* tileMap);
		void RemoveTileMap(TileMap *tileMap);
		static Rect CreateSweptBroadPhaseRect(Box b);
		static bool AABBCheck(Rect b1, Rect b2);
	private:
		void UpdateCollisionList();
		void UpdateBody();
		PhysicsMode physicsMode;
		Game *game;
		std::list<Body*> bodyList;
		std::list<GameObject*> collisionList;
		std::vector<TileMap*> tileMapList;

	};
}