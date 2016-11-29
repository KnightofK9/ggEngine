#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class AxeItem : public ItemBase {
public:
	AxeItem(CVGame *cvgame, SpriteInfo *image);
	~AxeItem();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};