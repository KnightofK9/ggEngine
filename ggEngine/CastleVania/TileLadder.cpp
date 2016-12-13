#include "TileLadder.h"
#include "TypeEnum.h"
TileLadder::TileLadder(CVGame * cvGame, SpriteInfo * info) : StaticTile(cvGame,info)
{
}

void TileLadder::SetTag(Tag tag)
{
	this->tag = tag;
	switch (tag) {
	case ObjectType_LadderDownLeft:
		break;
	case ObjectType_LadderUpRight:
		break;
	case ObjectType_LadderDownRight:
		break;
	case ObjectType_LadderUpLeft:
		break;
	}
}

double TileLadder::GetMoveToPositionX(double deltaX)
{
	switch (this->tag) {
	case ObjectType_LadderDownLeft:
	case ObjectType_LadderUpLeft:
		return this->position.x - deltaX;
		break;
	case ObjectType_LadderUpRight:
	case ObjectType_LadderDownRight:
		return this->position.x + this->GetWidth() + deltaX;
		break;
		break;
	}
}



TileLadder::~TileLadder()
{
}
