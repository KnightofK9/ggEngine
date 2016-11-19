#include "TileBase.h"

TileBase::TileBase(DrawManager * drawManager, TileMap * tileMap, SpriteInfo * image)  : SingleTile(drawManager, tileMap, image)
{
}

TileBase::~TileBase()
{
}
