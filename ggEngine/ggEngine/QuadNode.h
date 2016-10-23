#pragma once
#include <vector>
#include <d3d9.h>
#include "Vector.h"
namespace ggEngine {
	class DrawObject;
	class QuadTree;
	class QuadNode {
	public:
		QuadNode(QuadTree *quadTree,double width, double height,int id, int leftTop, int rightTop, int leftBottom, int rightBottom);
		QuadNode(QuadTree *quadTree, double width, double height,int id, std::vector<DrawObject*> objectList);
		~QuadNode();
		RECT GetRect();
		void SetObject(std::vector<DrawObject*> objectList);
		std::vector<DrawObject*> GetObjectFromNode();
		QuadNode* GetLeftTop();
		QuadNode* GetRightTop();
		QuadNode* GetLeftBottom();
		QuadNode* GetRightBottom();
	private:
		int leftTop, rightTop, leftBottom, rightBottom;
		std::vector<DrawObject*> objectList;
		double width, height;
		Vector position;
		int id;
		QuadTree *quadTreeParent;
	};
	
}