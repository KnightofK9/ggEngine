#pragma once
#include "ComponentBase.h"
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
	class Physics:public ComponentBase {
	public:
		Physics(Game *game,PhysicsMode physicsMode);
		~Physics();

		void Update(double dt) override;

		void UpdatePhysics();
		void EnablePhysics(GameObject * gameObject);
		void AttachBodyTo(GameObject *gameObject);
		void RemoveBodyFromList(Body *body);
		void Reset() override;
		void AddTileMap(TileMap* tileMap);
		void RemoveTileMap(TileMap *tileMap);
		std::list<Body*> GetBodyList() { return this->bodyList; }
		static Rect CreateSweptBroadPhaseRect(Box b);
		static bool AABBCheck(Rect b1, Rect b2);
		static Box CreateBoxFromObject(GameObject *go, Vector velocity);
		static ColliderArg CreateOppositeColliderArg(ColliderArg e, GameObject* otherObject);
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