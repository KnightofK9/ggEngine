#include "QuadTree.h"
namespace ggEngine {
	template<class T>
	QuadTree<T>::QuadTree(double x, double y, double width, double height)
	{
		this->width = width;
		this->height = height;
		this->rootNode = nullptr;
		this->position = Vector(x, y);
	}
	template<class T>
	QuadTree<T>::~QuadTree()
	{
		if (rootNode != nullptr) delete rootNode;
	}
	template<class T>
	void QuadTree<T>::SetRootNode(QuadNode<T>* rootNode)
	{
		this->rootNode = rootNode;
	}
	template<class T>
	QuadNode<T> QuadTree<T>::GetRootNode()
	{
		return this->rootNode;
	}
	template<class T>
	RECT QuadTree<T>::GetRect()
	{
		return{ position.x,position.y,position.x + width,position.y + height };
	}
}