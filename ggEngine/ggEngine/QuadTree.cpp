#include "QuadTree.h"
namespace ggEngine {
	QuadTree::QuadTree(double x, double y, double width, double height)
	{
		this->width = width;
		this->height = height;
		this->rootNode = nullptr;
		this->position = Vector(x, y);
	}
	QuadTree::~QuadTree()
	{
		if (rootNode != nullptr) delete rootNode;
	}
	void QuadTree::SetRootNode(QuadNode* rootNode)
	{
		this->rootNode = rootNode;
	}
	QuadNode* QuadTree::GetRootNode()
	{
		return this->rootNode;
	}
	RECT QuadTree::GetRect()
	{
		return{ (long)position.x,(long)position.y,(long)position.x + (long)width,(long)position.y + (long)height };
	}
}