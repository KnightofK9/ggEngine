#include "BreakableTileBrick.h"
#include "TypeEnum.h"
#include "CVGame.h"
#include "Simon.h"
#include "ItemBase.h"
BreakableTileBrick::BreakableTileBrick(CVGame * cvGame, SpriteInfo * image) : DropObjectBase(cvGame,image,16,16,0,1)
{
	this->tag = ObjectType_BreakableTileBrick;
}


BreakableTileBrick::~BreakableTileBrick()
{
}




void BreakableTileBrick::Active()
{
	BreakableObjectBase::Active();
}

void BreakableTileBrick::Draw()
{
	BreakableObjectBase::Draw();
}


