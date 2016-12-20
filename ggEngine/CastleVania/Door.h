#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
using namespace ggEngine;
class Door : public CVSpriteAnimation {
public:
	Door(CVGame *cvGame, SpriteInfo *image);
	virtual ~Door();
	void OpenDoor(bool isLeft);
	void CloseDoor();
	void ResetDoor();
private:
	void SetFacingDirection(bool isLeft);
	bool isLeft;
};