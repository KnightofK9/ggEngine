#include "QuadNode.h"

template<class T>
ggEngine::QuadNode<T>::QuadNode(double width, double height)
{
	leftTop = rightTop = leftBottom = rightBottom = object = nullptr;
	this->width = width;
	this->height = height;
}

template<class T>
ggEngine::QuadNode<T>::~QuadNode()
{
	if (object != nullptr) delete object;
}

template<class T>
RECT ggEngine::QuadNode<T>::GetRect()
{
	return{ position.x,position.y,position.x + width,position.y + height };
}
