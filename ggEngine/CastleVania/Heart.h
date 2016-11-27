#pragma once
#include <ggEngine.h>
#include "ItemBase.h"
using namespace ggEngine;
class Heart : public ItemBase {
public:
	Heart(CVGame *cvgame, SpriteInfo *image);
	~Heart();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
	const int healthGain = 1;
};