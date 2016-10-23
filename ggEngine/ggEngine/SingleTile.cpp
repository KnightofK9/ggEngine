#include "SingleTile.h"
#include "TileMap.h"
namespace ggEngine {
	SingleTile::SingleTile(DrawManager * drawManager, TileMap *tileMap , SpriteInfo * image) :Sprite(drawManager, image)
	{
		this->SetAnchor(0, 0);
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