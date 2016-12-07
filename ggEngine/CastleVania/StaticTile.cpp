#include "StaticTile.h"
#include "CVGame.h"
StaticTile::StaticTile(CVGame *cvGame,  SpriteInfo *image): CVSprite(cvGame,image)
{
	this->tag = ObjectType_Static;
	cvGame->physics->AttachBodyTo(this);
	this->body->CreateRectangleRigidBody(GetWidth(), GetHeight());
}

StaticTile::~StaticTile()
{
}
