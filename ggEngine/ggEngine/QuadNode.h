#pragma once
#include <vector>
#include <d3d9.h>
#include <list>
#include "Vector.h"
#include "GameObject.h"
namespace ggEngine {
	struct Bounds {
		double x;
		double y;
		double width;
		double height;
		double subWidth;
		double subHeight;
		double right;
		double bottom;
	/*width: width,
		height : height,
		subWidth : Math.floor(width / 2),
		subHeight : Math.floor(height / 2),
		right : Math.round(x) + Math.floor(width / 2),
		bottom : Math.round(y) + Math.floor(height / 2)*/
	};
	class QuadNode {
	public:
		QuadNode(double x, double y, double width, double height, unsigned int maxObjects, unsigned int maxLevels);
		~QuadNode();
		
	private:
		unsigned int maxObjects;
		unsigned int maxLevels;
		unsigned int level;
		std::vector<QuadNode*> nodes;
		std::vector<GameObject *> objects;
		Bounds bounds;
	};
	
}