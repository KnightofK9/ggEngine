#pragma once
#include <ggEngine.h>
#include "BreakableObjectBase.h"

using namespace ggEngine;
class CVGame;
class WeaponWhip;
class WeaponBase;
class BreakableTileBrick : public BreakableObjectBase
{
public:
	BreakableTileBrick(CVGame *cvGame, SpriteInfo *image);
	virtual ~BreakableTileBrick();

	void OnWeaponWhipContact(WeaponWhip *whip, ColliderArg e) override;
	void OnSubWeaponContact(WeaponBase *weapon, ColliderArg e) override;
	void SetDropItem(std::string itemJson);
	void Active() override;
private:
	void DropItem();
	std::string itemJson = "";
	//CVGame *cvGame;

};

