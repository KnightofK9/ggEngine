#include "QuadNode.h"

ggEngine::QuadNode::QuadNode(double width, double height)
{
	leftTop = rightTop = leftBottom = rightBottom = -1;
	this->object = nullptr;
	this->width = width;
	this->height = height;
}

ggEngine::QuadNode::~QuadNode()
{
	if (object != nullptr) delete object;
}

RECT ggEngine::QuadNode::GetRect()
{
	return{ (long)position.x,(long)position.y,(long)position.x + (long)width,(long)position.y + (long)height };
}
