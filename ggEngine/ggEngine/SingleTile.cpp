#include "SingleTile.h"
#include "TileMap.h"
#include "QuadNode.h"
namespace ggEngine {
	SingleTile::SingleTile(DrawManager * drawManager, TileMap *tileMap , SpriteInfo * image) :Sprite(drawManager, image)
	{
		SetAnchor(0, 0);
		SetPosition(0, 0);
		SetParentObject(tileMap);
	}
	void SingleTile::Draw()
	{
		Sprite::Draw();
	}
	SingleTile::~SingleTile()
	{
	}
}