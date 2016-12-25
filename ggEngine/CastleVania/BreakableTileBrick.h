#pragma once
#include <ggEngine.h>
#include "DropObjectBase.h"

using namespace ggEngine;
class CVGame;
class WeaponWhip;
class WeaponBase;
class BreakableTileBrick : public DropObjectBase
{
public:
	BreakableTileBrick(CVGame *cvGame, SpriteInfo *image);
	virtual ~BreakableTileBrick();

	void Active() override;
	void Draw() override;
private:

};

