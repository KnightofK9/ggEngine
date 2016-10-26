#include "QuadNode.h"
#include "QuadTree.h"
#include "TileMap.h"
#include "SingleTile.h"
#include "AnimationTile.h"
namespace ggEngine {

	QuadNode::QuadNode(QuadTree * quadTree, double width, double height,int id, int leftTop, int rightTop, int leftBottom, int rightBottom)
	{
		this->quadTreeParent = quadTree;
		this->id = id;
		this->width = width;
		this->height = height;
		this->leftTop = leftTop;
		this->rightTop = rightTop;
		this->leftBottom = leftBottom;
		this->rightBottom = rightBottom;
		this->isLeafNode = false;
		SetParentObject(quadTree->tileMap);
	}

	QuadNode::QuadNode(QuadTree * quadTree, double width, double height,int id)
	{
		this->quadTreeParent = quadTree;
		this->id = id;
		this->width = width;
		this->height = height;
		this->leftTop = this->rightTop = this->leftBottom = this->rightBottom = -1;
		this->isLeafNode = true;
		SetParentObject(quadTree->tileMap);
	}

	QuadNode::~QuadNode()
	{
		for (auto it = objectList.begin(); it != objectList.end(); ++it) {
			delete (*it);
		}
		objectList.clear();
	}

	RECT QuadNode::GetRect()
	{
		return{ (long)position.x,(long)position.y,(long)position.x + (long)width,(long)position.y + (long)height };
	}
	QuadNode * QuadNode::GetLeftTop()
	{
		if (this->leftTop == -1) return nullptr;
		return this->quadTreeParent->GetNodeAt(this->leftTop);
	}
	QuadNode * QuadNode::GetRightTop()
	{
		if (this->rightTop == -1) return nullptr;
		return this->quadTreeParent->GetNodeAt(this->rightTop);
	}
	QuadNode * QuadNode::GetLeftBottom()
	{
		if (this->leftBottom == -1) return nullptr;
		return this->quadTreeParent->GetNodeAt(this->leftBottom);
	}
	QuadNode * QuadNode::GetRightBottom()
	{
		if (this->rightBottom == -1) return nullptr;
		return this->quadTreeParent->GetNodeAt(this->rightBottom);
	}
	void QuadNode::Draw()
	{
		for (int i = 0; i < this->objectList.size(); i++) {
			SingleTile *tile = dynamic_cast<SingleTile*>(objectList[i]);
			/*this->objectList[i]->UpdateWorldPosition();
			this->objectList[i]->Draw();*/
			tile->UpdateWorldPosition();
			tile->Draw();
		}
		/*for (auto it = this->objectList.begin(); it != this->objectList.end(); ++it) {
			if ((*it)->IsVisible()) {
				(*it)->UpdateWorldPosition();
				(*it)->Draw();
			}
		}*/
	}
	void QuadNode::SetObject(std::vector<GameObject*>  objectList)
	{
		this->objectList = objectList;
	}
	std::vector<GameObject*> QuadNode::GetObjectFromNode()
	{
		return this->objectList;
	}
}
