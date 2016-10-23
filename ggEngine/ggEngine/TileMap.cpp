#include "TileMap.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "QuadTree.h"
#include "QuadNode.h"
#include "SpriteInfo.h"
#include "AnimationTile.h"
#include "SingleTile.h"
namespace ggEngine {
	TileMap::TileMap(DrawManager* drawManager)
	{
		this->quadTree = nullptr;
		this->drawManager = drawManager;
		this->spriteHandle = drawManager->GetSpriteHandle();
	}
	TileMap::~TileMap()
	{
		if (quadTree != nullptr) delete quadTree;
	}
	void TileMap::Draw(const RECT drawRect)
	{
		RecursiveDraw(drawRect, this->quadTree->GetRootNode());
	}
	void TileMap::CheckCollision(const GameObject * gameObject)
	{
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
				(*it)->Draw();
			}
			return;
		}
		RecursiveDraw(drawRect, quadNode->GetLeftTop(), isDrawAllChildNode);
		RecursiveDraw(drawRect, quadNode->GetRightTop(), isDrawAllChildNode);
		RecursiveDraw(drawRect, quadNode->GetLeftBottom(), isDrawAllChildNode);
		RecursiveDraw(drawRect, quadNode->GetRightBottom(), isDrawAllChildNode);
		return;

	}
	void TileMap::ParseJson(const char * jsonChar)
	{

	}
	const char * TileMap::CreateJson()
	{
		Json json;
		//json.AddMember("x", x, json.GetAllocator());
		return json.GetCharArray();
	}
}