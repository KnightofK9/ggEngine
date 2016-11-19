#include "StaticTile.h"

StaticTile::StaticTile(Physics *physics, DrawManager * drawManager, TileMap * tileMap, SpriteInfo * image): TileBase(drawManager,tileMap,image)
{
	this->tag = ObjectType_Static;
	physics->AttachBodyTo(this);
	this->body->CreateRectangleRigidBody(width, height);
}

StaticTile::~StaticTile()
{
}
