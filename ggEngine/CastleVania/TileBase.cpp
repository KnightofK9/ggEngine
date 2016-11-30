#include "TileBase.h"
#include "CVGame.h"
TileBase::TileBase(CVGame *cvGame, TileMap * tileMap, SpriteInfo * image)  : SingleTile(cvGame, tileMap, image)
{
}

TileBase::~TileBase()
{
}
