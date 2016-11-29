#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class BoomerangItem : public ItemBase {
public:
	BoomerangItem(CVGame *cvgame, SpriteInfo *image);
	~BoomerangItem();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};