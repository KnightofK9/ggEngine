#include "TileMap.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "QuadTree.h"
#include "QuadNode.h"
#include "SpriteInfo.h"
#include "AnimationTile.h"
#include "SingleTile.h"
#include "Camera.h"
namespace ggEngine {
	TileMap::TileMap(Camera *camera, DrawManager* drawManager, Cache *cache) 
	{
		this->quadTree = nullptr;
		this->cache = cache;
		this->drawManager = drawManager;
		this->spriteHandle = drawManager->GetSpriteHandle();
	}
	TileMap::~TileMap()
	{
		if (quadTree != nullptr) delete quadTree;
	}
	/*void TileMap::Draw()
	{
		const RECT drawRect = camera->GetRect();
		RecursiveDraw(drawRect, this->quadTree->GetRootNode());
	}*/

	std::list<DrawObject*>* TileMap::GetDrawList(){
		this->drawList.clear();
		const RECT drawRect = camera->GetRect();
		RecursiveDraw(drawRect, this->quadTree->GetRootNode());
		return &this->drawList;
	}
	void TileMap::CheckCollision(const GameObject * gameObject)
	{

	}
	void TileMap::BuildTree(std::string location)
	{
		Json json(location);
		this->quadTree = new QuadTree(this, this->drawManager, this->cache);
		quadTree->BuildTree(json.GetCharArray());
	}
	void TileMap::RecursiveDraw(const RECT & drawRect, QuadNode * quadNode, bool isDrawAllChildNode)
	{
		if (!isDrawAllChildNode) {
			RECT intersectRect;
			if (!IntersectRect(&intersectRect, &drawRect, &quadNode->GetRect())) {
				return;
			}
			if (intersectRect.left == intersectRect.top == intersectRect.right == intersectRect.bottom == 0) {
				isDrawAllChildNode = true;
			}
		}
		std::vector<DrawObject *> objectList = quadNode->GetObjectFromNode();
		if (objectList.size()>0) {
			for (auto it = objectList.begin(); it != objectList.end(); ++it) {
				//(*it)->Draw();
				this->drawList.push_back((*it));
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