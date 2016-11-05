#pragma once
#include "Group.h"
#include "GameObject.h"
namespace ggEngine {
	class QuadTree;
	class SpriteInfo;
	class DrawManager;
	class QuadNode;
	class Cache;
	class Camera;
	class TileMap : public Group{
	public:
		TileMap(Camera *camera, DrawManager* drawManager, Cache *cache);
		~TileMap();
		void CheckCollision(const GameObject *gameObject);
		void BuildTree(std::string location);
		std::list<GameObject*> *GetDrawList();
		void UpdateWorldPosition() override;
	private:
		Camera *camera;
		void RecursiveDraw(const RECT &drawRect, QuadNode *quadNode, bool isDrawChildNode = false);
		QuadTree *quadTree;
		LPD3DXSPRITE spriteHandle;
		Cache *cache;
		DrawManager *drawManager;



	};
}