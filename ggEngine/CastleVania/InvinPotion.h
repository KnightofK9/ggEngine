#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class InvinPotion : public ItemBase {
public:
	InvinPotion(CVGame *cvgame, SpriteInfo *image);
	~InvinPotion();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};