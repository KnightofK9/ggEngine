#pragma once
#include "Vector.h"
#include <d3d9.h>
namespace ggEngine {
	class GameObject;
	class QuadNode {
	public:
		QuadNode(double width, double height);
		~QuadNode();
		RECT GetRect();
		void SetObject(GameObject *object);
		GameObject* GetObjectFromNode();
		int leftTop, rightTop, leftBottom, rightBottom;
	private:
		GameObject *object;
		double width, height;
		Vector position;
	};
	inline void QuadNode::SetObject(GameObject * object)
	{
		this->object = object;
	}
	inline GameObject* QuadNode::GetObjectFromNode()
	{
		if (this->object != nullptr) return this->object;
	}
}