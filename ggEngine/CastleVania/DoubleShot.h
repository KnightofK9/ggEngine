#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class DoubleShot : public ItemBase {
public:
	DoubleShot(CVGame *cvgame, SpriteInfo *image);
	~DoubleShot();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
	int shot = 2;
};