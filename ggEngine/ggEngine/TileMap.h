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
	class SingleTile;
	class TileMap : public Group{
	public:
		TileMap(Camera *camera, DrawManager* drawManager, Cache *cache, Physics *physics);
		~TileMap();
		void Destroy();
		void Update() override;
		void BuildTree(std::string jsonChar, bool isLocation = false);
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
		double tileWidth;
		double tileHeight;
		bool isUsedQuadTree;
		std::vector<SingleTile*> tileList;
		std::vector<std::string> tileSetKeyList;



	};
}