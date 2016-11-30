#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class HolyWaterItem : public ItemBase {
public:
	HolyWaterItem(CVGame *cvgame, SpriteInfo *image);
	~HolyWaterItem();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};