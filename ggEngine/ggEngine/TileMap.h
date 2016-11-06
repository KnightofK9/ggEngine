#pragma once
#include "Group.h"
#include "GameObject.h"
#include <vector>
namespace ggEngine {
	class QuadTree;
	class SpriteInfo;
	class DrawManager;
	class QuadNode;
	class Cache;
	class Camera;
	class Physics;
	class TileMap : public Group{
	public:
		TileMap(Camera *camera, DrawManager* drawManager, Cache *cache, Physics *physics);
		~TileMap();
		void Destroy();
		void Update() override;
		void BuildTree(std::string location);
		std::list<GameObject*> *GetDrawList();
		std::list<GameObject*> GetCollisionCheckList();
		void UpdateWorldPosition() override;
	private:
		std::list<GameObject*> collisionCheckList;
		Camera *camera;
		Physics* physics;
		void RecursiveDraw(const RECT &drawRect, QuadNode *quadNode, bool isDrawChildNode = false);
		QuadTree *quadTree;
		LPD3DXSPRITE spriteHandle;
		Cache *cache;
		DrawManager *drawManager;



	};
}