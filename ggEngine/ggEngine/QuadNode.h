#pragma once
#include "Vector.h"
#include <d3d9.h>
namespace ggEngine {
	class GameObject;
	class QuadTree;
	class QuadNode {
	public:
		QuadNode(QuadTree *quadTree,double width, double height);
		~QuadNode();
		RECT GetRect();
		void SetObject(GameObject *object);
		GameObject* GetObjectFromNode();
		QuadNode* GetLeftTop();
		QuadNode* GetRightTop();
		QuadNode* GetLeftBottom();
		QuadNode* GetRightBottom();
	private:
		int leftTop, rightTop, leftBottom, rightBottom;
		GameObject *object;
		double width, height;
		Vector position;
		QuadTree *quadTreeParent;
	};
	
}