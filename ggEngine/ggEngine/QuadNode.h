#pragma once
#include <vector>
#include <d3d9.h>
#include <list>
#include "Vector.h"
#include "GameObject.h"
namespace ggEngine {
	class Group;
	class Body;
	class QuadTree;
	class Game;
	struct Bounds {
		double x;
		double y;
		double width;
		double height;
		double subWidth;
		double subHeight;
		double right;
		double bottom;
	};
	class QuadNode {
	public:
		QuadNode(Game *game, QuadTree *quadTree,double x, double y, double width, double height, unsigned int maxObjects, unsigned int maxLevels, unsigned int level);
		QuadNode(Game *game, QuadTree *quadTree,const char* quadNodeJson);
		~QuadNode();
		void Reset(double x, double y, double width, double height, unsigned int maxObjects, unsigned int maxLevels, unsigned int level);
		void Populate(Group *group);
		void Split();
		void Insert(Body * body);
		int GetIndex(Rect rect);
		void Retrieve(std::list<Body*> *retrieveList, Rect source);
		void Clear();
		std::vector<QuadNode*> nodes;

	private:
		QuadTree *quadTree = nullptr;
		void InsertFromDrawList(std::list<GameObject*> drawList);
		unsigned int maxObjects;
		unsigned int maxLevels;
		unsigned int level;
		std::vector<Body *> objects;
		Bounds bounds;
		Game *game = nullptr;
	};
	
}