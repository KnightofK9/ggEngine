#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class HeartLarger : public ItemBase {
public:
	HeartLarger(CVGame *cvgame, SpriteInfo *image);
	~HeartLarger();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
	int point = 5;
};