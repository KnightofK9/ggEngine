#include "QuadNode.h"
namespace ggEngine {
	QuadNode::QuadNode(double x, double y, double width, double height, unsigned int maxObjects, unsigned int maxLevels)
	{
		bounds.x = round(x);
		bounds.y = round(y);
		bounds.width = width;
		bounds.height = height;
		bounds.subWidth = floor(width / 2);
		bounds.subHeight = floor(height / 2);
		bounds.right = bounds.x + bounds.subWidth;
		bounds.bottom = bounds.y + bounds.subHeight;
	}
	QuadNode::~QuadNode()
	{
	}

}
