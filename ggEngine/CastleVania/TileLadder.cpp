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

TileLadder::~TileLadder()
{
}
