#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class WhipUpgradeItem : public ItemBase {
public:
	WhipUpgradeItem(CVGame *cvgame, SpriteInfo *image);
	~WhipUpgradeItem();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};