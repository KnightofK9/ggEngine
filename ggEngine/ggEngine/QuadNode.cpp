#include "QuadNode.h"
#include "QuadTree.h"

namespace ggEngine {
	QuadNode::QuadNode(QuadTree *quadTree, double width, double height)
	{
		leftTop = rightTop = leftBottom = rightBottom = -1;
		this->object = nullptr;
		this->width = width;
		this->height = height;
		this->quadTreeParent = quadTree;
	}

	QuadNode::~QuadNode()
	{
		if (object != nullptr) delete object;
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
	void QuadNode::SetObject(GameObject * object)
	{
		this->object = object;
	}
	GameObject* QuadNode::GetObjectFromNode()
	{
		if (this->object != nullptr) return this->object;
	}
}
