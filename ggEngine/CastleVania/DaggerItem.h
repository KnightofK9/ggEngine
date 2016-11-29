#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class DaggerItem : public ItemBase {
public:
	DaggerItem(CVGame *cvgame, SpriteInfo *image);
	~DaggerItem();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};