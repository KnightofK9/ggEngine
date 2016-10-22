#pragma once
#include "QuadNode.h"
namespace ggEngine {
	class QuadTree {
	public:
		QuadTree(double x, double y,double width, double height);
		~QuadTree();
		void SetRootNode(QuadNode *rootNode);
		QuadNode* GetRootNode();
		RECT GetRect();
	private:
		Vector position;
		double width, height;
		QuadNode *rootNode;
	};
}