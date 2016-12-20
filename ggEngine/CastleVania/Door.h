#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
using namespace ggEngine;
class Door : public CVSpriteAnimation {
public:
	Door(CVGame *cvGame, SpriteInfo *image);
	virtual ~Door();
	void OpenDoor();
	void CloseDoor();
	void ResetDoor();
private:
};