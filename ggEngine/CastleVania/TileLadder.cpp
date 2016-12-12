#include "TileLadder.h"
#include "TypeEnum.h"
TileLadder::TileLadder(CVGame * cvGame, SpriteInfo * info) : StaticTile(cvGame,info)
{
	this->body->CreateRectangleRigidBody(GetWidth()/2, GetHeight()/2);
}

TileLadder::~TileLadder()
{
}
