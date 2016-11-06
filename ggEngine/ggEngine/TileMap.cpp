#include "TileMap.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "QuadTree.h"
#include "QuadNode.h"
#include "SpriteInfo.h"
#include "AnimationTile.h"
#include "SingleTile.h"
#include "Camera.h"
#include "Physics.h"
#include "Debug.h"
namespace ggEngine {
	TileMap::TileMap(Camera *camera, DrawManager* drawManager, Cache *cache, Physics *physics) 
	{
		this->quadTree = nullptr;
		this->camera = camera;
		this->physics = physics;
		this->cache = cache;
		this->drawManager = drawManager;
		this->spriteHandle = drawManager->GetSpriteHandle();
		SetScale(1, 1);
	}
	TileMap::~TileMap()
	{
		if (quadTree != nullptr) delete quadTree;
		this->physics->RemoveTileMap(this);
	}
	void TileMap::Destroy()
	{
		this->alive = false;
	}
	void TileMap::Update()
	{
		Group::Update();
		/*Update check collision and draw list*/
		this->collisionCheckList.clear();
		this->drawList.clear();
		const RECT drawRect = camera->GetRect();
		RecursiveDraw(drawRect, this->quadTree->GetRootNode());
	}

	std::list<GameObject*>* TileMap::GetDrawList(){
	
		//g_debug.Log("Current draw size " + std::to_string(this->drawList.size()));
		return &this->drawList;
	}
	std::list<GameObject*> TileMap::GetCollisionCheckList()
	{
		return this->collisionCheckList;
	}
	void TileMap::UpdateWorldPosition()
	{
		GameObject::UpdateWorldPosition();
		this->quadTree->GetRootNode()->UpdateWorldPositionFromTileMap();
		std::vector<QuadNode*> *quadNodeList = this->quadTree->GetQuadNodeListAsRef();
		for (auto it = quadNodeList->begin(); it != quadNodeList->end(); ++it) {
			((*it))->UpdateWorldPositionFromTileMap();
		}
	}
	void TileMap::BuildTree(std::string location)
	{
		Json json(location,true);
		this->quadTree = new QuadTree(this, this->drawManager, this->cache, this->physics);
		quadTree->BuildTree(json.GetCharArray());
	}
	void TileMap::RecursiveDraw(const RECT & drawRect, QuadNode * quadNode, bool isDrawAllChildNode)
	{
		if (!isDrawAllChildNode) {
			RECT intersectRect;
			RECT b = quadNode->GetRect();
			if (!IntersectRect(&intersectRect, &drawRect,&b)) {
				return;
			}
			if (intersectRect.left == b.left  && intersectRect.top == b.top && intersectRect.right == b.right  && intersectRect.bottom == b.bottom ) {
				isDrawAllChildNode = true;
			}
		}
		//std::vector<DrawObject *> objectList = quadNode->GetObjectFromNode();
		//if (objectList.size()>0) {
		//	for (auto it = objectList.begin(); it != objectList.end(); ++it) {
		//		//(*it)->Draw();
		//		this->drawList.push_back((*it));
		//	}
		//	return;
		//}
		
		if (quadNode->IsLeafNode()) {
			this->drawList.push_back(quadNode);
			if (quadNode->IsCollidedObject()) {
				this->collisionCheckList.push_back(quadNode);
			}
			return;
		}
		RecursiveDraw(drawRect, quadNode->GetLeftTop(), isDrawAllChildNode);
		RecursiveDraw(drawRect, quadNode->GetRightTop(), isDrawAllChildNode);
		RecursiveDraw(drawRect, quadNode->GetLeftBottom(), isDrawAllChildNode);
		RecursiveDraw(drawRect, quadNode->GetRightBottom(), isDrawAllChildNode);
		return;

	}
}