#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class Crown : public ItemBase {
public:
	Crown(CVGame *cvgame, SpriteInfo *image);
	~Crown();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
};