#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class MoneyBag100 : public ItemBase {
public:
	MoneyBag100(CVGame *cvgame, SpriteInfo *image);
	~MoneyBag100();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
	int money = 100;
};