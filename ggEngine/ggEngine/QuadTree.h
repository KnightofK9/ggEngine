#pragma once
#include "QuadNode.h"
namespace ggEngine {
	template<class T>
	class QuadTree {
	public:
		QuadTree(double x, double y,double width, double height);
		~QuadTree();
		void SetRootNode(QuadNode<T> *rootNode);
		QuadNode<T> GetRootNode();
		RECT GetRect();
	private:
		Vector position;
		double width, height;
		QuadNode<T> *rootNode;
	};
}