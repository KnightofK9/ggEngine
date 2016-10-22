#include "QuadTree.h"
namespace ggEngine {
	QuadTree::QuadTree(double x, double y, double width, double height, int quadNodeListSize)
	{
		this->width = width;
		this->height = height;
		this->position = Vector(x, y);
		this->quadNodeList.reserve(quadNodeListSize);
	}
	QuadTree::~QuadTree()
	{
		for (auto it = quadNodeList.begin(); it != quadNodeList.end(); ++it) {
			delete (*it);
		}
		quadNodeList.clear();
	}
	QuadNode* QuadTree::GetRootNode()
	{
		if(this->quadNodeList.size()>0)
			return this->quadNodeList[0];
	}
	RECT QuadTree::GetRect()
	{
		return{ (long)position.x,(long)position.y,(long)position.x + (long)width,(long)position.y + (long)height };
	}
	QuadNode * QuadTree::GetNodeAt(int index)
	{
		return quadNodeList[index];
	}
}