#include "StaticTile.h"
#include "CVGame.h"
StaticTile::StaticTile(CVGame *cvGame, TileMap *tileMap, SpriteInfo *image): TileBase(cvGame,tileMap,image)
{
	this->tag = ObjectType_Static;
	cvGame->physics->AttachBodyTo(this);
	this->body->CreateRectangleRigidBody(width, height);
}

StaticTile::~StaticTile()
{
}
