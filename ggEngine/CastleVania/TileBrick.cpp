#include "TileBrick.h"
#include "CVGame.h"
#include "TypeEnum.h"
TileBrick::TileBrick(CVGame * cvGame, SpriteInfo * info) : StaticTile(cvGame,info)
{
	this->tag = ObjectType_LevelTwoBrick;
	this->visible = false;
}

TileBrick::~TileBrick()
{
}
