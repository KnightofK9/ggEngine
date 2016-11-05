#include "QuadNode.h"
#include "QuadTree.h"
#include "TileMap.h"
#include "SingleTile.h"
#include "AnimationTile.h"
#include "Debug.h"
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
		this->isCollidedObject = false;
		SetScale(1, 1);
		SetParentObject(quadTree->tileMap);
	}

	QuadNode::QuadNode(QuadTree * quadTree, double width, double height,int id, bool isCollidedObject)
	{
		this->quadTreeParent = quadTree;
		this->id = id;
		this->width = width;
		this->height = height;
		this->leftTop = this->rightTop = this->leftBottom = this->rightBottom = -1;
		this->isLeafNode = true;
		this->isCollidedObject = isCollidedObject;
		SetScale(1, 1);
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
		return{ (long)(worldPosition.x) - 1,(long)(worldPosition.y) - 1,(long)(worldPosition.x + width*worldScale.x) + 1,(long)(worldPosition.y + height*worldScale.y) + 1 };
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
	void QuadNode::UpdateWorldPosition()
	{
		/*GameObject::UpdateWorldPosition();*/
		/*for (int i = 0; i < this->objectList.size(); i++) {
			this->objectList[i]->UpdateWorldPosition();
		}*/
	}
	void QuadNode::UpdateWorldPositionFromTileMap()
	{
		this->worldScale = Vector(this->scale.x*this->parentObject->worldScale.x, this->scale.y*this->parentObject->worldScale.y);
		this->worldPosition = Vector(this->position.x*this->parentObject->worldScale.x, this->position.y*this->parentObject->worldScale.y) + this->parentObject->worldPosition;

	}
	void QuadNode::Draw()
	{
		for (int i = 0; i < this->objectList.size(); i++) {
			/*SingleTile *tile = dynamic_cast<SingleTile*>(objectList[i]);
			
			tile->UpdateWorldPosition();
			tile->Draw();*/
			this->objectList[i]->UpdateWorldPosition();
			this->objectList[i]->Draw();
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
