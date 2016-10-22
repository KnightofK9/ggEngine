#include "TileMap.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "QuadTree.h"
#include "QuadNode.h"
namespace ggEngine {
	TileMap::TileMap(DrawManager* drawManager)
	{
		this->quadTree = nullptr;
		this->texture = nullptr;
		this->drawManager = drawManager;
		this->spriteHandle = drawManager->GetSpriteHandle();
	}
	TileMap::~TileMap()
	{
		if (quadTree != nullptr) delete quadTree;
		if (texture != nullptr) delete texture;
	}
	void TileMap::Draw(const RECT drawRect)
	{
		RecuresiveDraw(drawRect, this->quadTree->GetRootNode());
	}
	void TileMap::ParseTree(const char * json)
	{
	}
	void TileMap::RecuresiveDraw(const RECT & drawRect, QuadNode * quadNode)
	{

	}
}