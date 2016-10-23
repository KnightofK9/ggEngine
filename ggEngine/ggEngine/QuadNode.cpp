#include "QuadNode.h"
#include "QuadTree.h"
#include "DrawObject.h"
namespace ggEngine {

	QuadNode::QuadNode(QuadTree * quadTree, double width, double height,int id, int leftTop, int rightTop, int leftBottom, int rightBottom)
	{
		this->quadTreeParent = quadTree;
		this->id = id;
		this->width = width;
		this->height = height;
		this->leftTop = leftTop;
		this->rightTop = rightTop;
		this->leftBottom = leftBottom;
		this->rightBottom = rightBottom;
	}

	QuadNode::QuadNode(QuadTree * quadTree, double width, double height,int id, std::vector<DrawObject*> objectList)
	{
		this->quadTreeParent = quadTree;
		this->id = id;
		SetObject(objectList);
		this->width = width;
		this->height = height;
		this->leftTop = this->rightTop = this->leftBottom = this->rightBottom = -1;
	}

	QuadNode::~QuadNode()
	{
		for (auto it = objectList.begin(); it != objectList.end(); ++it) {
			delete (*it);
		}
		objectList.clear();
	}

	RECT QuadNode::GetRect()
	{
		return{ (long)position.x,(long)position.y,(long)position.x + (long)width,(long)position.y + (long)height };
	}
	QuadNode * QuadNode::GetLeftTop()
	{
		if (this->leftTop == -1) return nullptr;
		return this->quadTreeParent->GetNodeAt(this->leftTop);
	}
	QuadNode * QuadNode::GetRightTop()
	{
		if (this->rightTop == -1) return nullptr;
		return this->quadTreeParent->GetNodeAt(this->rightTop);
	}
	QuadNode * QuadNode::GetLeftBottom()
	{
		if (this->leftBottom == -1) return nullptr;
		return this->quadTreeParent->GetNodeAt(this->leftBottom);
	}
	QuadNode * QuadNode::GetRightBottom()
	{
		if (this->rightBottom == -1) return nullptr;
		return this->quadTreeParent->GetNodeAt(this->rightBottom);
	}
	void QuadNode::SetObject(std::vector<DrawObject*>  objectList)
	{
		this->objectList = objectList;
	}
	std::vector<DrawObject*> QuadNode::GetObjectFromNode()
	{
		return this->objectList;
	}
}
