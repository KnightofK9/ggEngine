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
	class Physics;
	class QuadTree {
	public:
		QuadTree(TileMap *tileMap,DrawManager *drawManager, Cache *cache, Physics* physics);
		~QuadTree();
		QuadNode* GetRootNode();
		void BuildTree(std::string jsonChar);
		RECT GetRect();
		QuadNode* GetNodeAt(int index);
		TileMap *tileMap;
		std::vector<QuadNode*> GetQuadNodeList() { return this->quadNodeList; }
		std::vector<QuadNode*> *GetQuadNodeListAsRef() { return &this->quadNodeList; }
		int GetNumberOfLeafNode() { return this->numberOfLeafNode; }
	private:
		DrawManager *drawManager;
		SingleTile* GetSpriteFromTileInfo(std::string tileMapKey, int tileId, double width, double height, QuadNode *parentNode);
		AnimationTile* GetSpriteAnimationFromTileInfo(rapidjson::Value const &tileList, double width, double height, QuadNode *parentNode);
		std::vector<QuadNode*> quadNodeList;
		Vector position;
		Cache *cache;
		Physics* physics;
		QuadNode *rootNode;
		double width, height;
		int numberOfLeafNode;
	};
}