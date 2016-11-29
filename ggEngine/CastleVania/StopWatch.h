#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class StopWatch : public ItemBase {
public:
	StopWatch(CVGame *cvgame, SpriteInfo *image);
	~StopWatch();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};