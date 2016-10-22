#pragma once
#include "QuadNode.h"
#include <vector>
namespace ggEngine {
	class QuadTree {
	public:
		QuadTree(double x, double y,double width, double height,int quadNodeListSize = 48);
		~QuadTree();
		QuadNode* GetRootNode();
		RECT GetRect();
		QuadNode* GetNodeAt(int index);
	private:
		std::vector<QuadNode*> quadNodeList;
		Vector position;
		double width, height;
	};
}