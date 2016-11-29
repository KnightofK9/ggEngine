#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class MoneyBag400 : public ItemBase {
public:
	MoneyBag400(CVGame *cvgame, SpriteInfo *image);
	~MoneyBag400();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
	int money = 400;
};