#pragma once
#include <ggEngine.h>
#include "ItemBase.h"

using namespace ggEngine;
class TripleShot : public ItemBase {
public:
	TripleShot(CVGame *cvgame, SpriteInfo *image);
	~TripleShot();

	void OnSimonContact(Simon *simon, ColliderArg e) override;
private:
	int shot = 3;
};