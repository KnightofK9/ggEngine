#pragma once
#include "Vector.h"
#include <d3d9.h>
namespace ggEngine {
	template<class T>
	class QuadNode {
	public:
		QuadNode(double width, double height);
		~QuadNode();
		RECT GetRect();
		void SetObject(T *object);
		T GetObjectFromNode();
		QuadNode *leftTop, *rightTop, *leftBottom, *rightBottom;
	private:
		T *object;
		double width, height;
		Vector position;
	};
	template<class T>
	inline void QuadNode<T>::SetObject(T * object)
	{
		this->object = object;
	}
	template<class T>
	inline T QuadNode<T>::GetObjectFromNode()
	{
		if (this->object != nullptr) return this->object;
	}
}