#pragma once
#include "BreakableObjectBase.h"
class DropObjectBase : public BreakableObjectBase {
public:
	DropObjectBase(CVGame *cvGame, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	virtual ~DropObjectBase();

	void SetDropItem(std::string itemJson);
protected:
	void DropItem();
	std::string itemJson = "";
};