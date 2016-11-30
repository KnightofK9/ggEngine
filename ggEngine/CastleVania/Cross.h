#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class Cross : public ItemBase {
public:
	Cross(CVGame *cvgame, SpriteInfo *image);
	virtual ~Cross();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};