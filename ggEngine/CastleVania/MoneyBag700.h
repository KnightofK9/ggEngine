#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class MoneyBag700 : public ItemBase {
public:
	MoneyBag700(CVGame *cvgame, SpriteInfo *image);
	~MoneyBag700();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
	int money = 700;
};