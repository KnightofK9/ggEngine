#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class PotRoast : public ItemBase {
public:
	PotRoast(CVGame *cvgame, SpriteInfo *image);
	~PotRoast();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
	const int healthPoint = 6;
};