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

	void QuadNode::Reset(double x, double y, double width, double height, unsigned int maxObjects, unsigned int maxLevels, unsigned int level)
	{
		this->maxObjects = maxObjects;
		this->maxLevels = maxLevels;
		this->level = level;

		this->bounds.x = round(x);
		this->bounds.y = round(y);

	}

	void QuadNode::Populate(Group * group)
	{
	}

	void QuadNode::Split()
	{
	}

	void QuadNode::Insert(GameObject * gameObject)
	{
	}

	int QuadNode::GetIndex(Rect rect)
	{
		return 0;
	}

	void QuadNode::Retrieve(std::list<GameObject*>* retrieveList, Rect rect)
	{
	}

	void QuadNode::Clear()
	{
	}

}
