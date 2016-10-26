#include "SingleTile.h"
#include "TileMap.h"
#include "QuadNode.h"
namespace ggEngine {
	SingleTile::SingleTile(DrawManager * drawManager, QuadNode *parentNode , SpriteInfo * image) :Sprite(drawManager, image)
	{
		SetAnchor(0, 0);
		SetPosition(0, 0);
		SetParentObject(parentNode);
	}
	void SingleTile::Draw()
	{
		Sprite::Draw();
	}
	SingleTile::~SingleTile()
	{
	}
}