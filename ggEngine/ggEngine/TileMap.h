#pragma once
#include "Group.h"
namespace ggEngine {
	class QuadTree;
	class SpriteInfo;
	class DrawManager;
	class QuadNode;
	class Cache;
	class TileMap : public Group{
	public:
		TileMap(DrawManager* drawManager, Cache *cache);
		~TileMap();
		void Draw(const RECT drawRect);
		void CheckCollision(const GameObject *gameObject);
		void BuildTree(std::string location);
	private:
		void RecursiveDraw(const RECT &drawRect, QuadNode *quadNode, bool isDrawChildNode = false);
		QuadTree *quadTree;
		DrawManager *drawManager;
		LPD3DXSPRITE spriteHandle;
		Cache *cache;

	};
}