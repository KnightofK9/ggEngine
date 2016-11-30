#include "SingleTile.h"
#include "TileMap.h"
#include "QuadNode.h"
namespace ggEngine {
	SingleTile::SingleTile(Game *game, TileMap *tileMap , SpriteInfo * image) :Sprite(game, image)
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