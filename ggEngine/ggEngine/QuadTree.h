#pragma once
#include <vector>
#include <string>
#include <d3d9.h>
#include "Vector.h"
#include "Json.h"
namespace ggEngine {
	class SingleTile;
	class AnimationTile;
	class Cache;
	class TileMap;
	class QuadNode;
	class DrawManager;
	class QuadTree {
	public:
		QuadTree(TileMap *tileMap,DrawManager *drawManager, Cache *cache);
		~QuadTree();
		QuadNode* GetRootNode();
		void BuildTree(std::string jsonChar);
		RECT GetRect();
		QuadNode* GetNodeAt(int index);
	private:
		TileMap *tileMap;
		DrawManager *drawManager;
		SingleTile* GetSpriteFromTileInfo(std::string tileMapKey, int tileId, double width, double height, QuadNode *parentNode);
		AnimationTile* GetSpriteAnimationFromTileInfo(rapidjson::Value const &tileList, double width, double height, QuadNode *parentNode);
		std::vector<QuadNode*> quadNodeList;
		Vector position;
		Cache *cache;
		QuadNode *rootNode;
		double width, height;
	};
}