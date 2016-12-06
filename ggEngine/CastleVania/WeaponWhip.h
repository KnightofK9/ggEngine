#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
#include <string>

using namespace ggEngine;
class CVGame;
class WeaponWhip : public CVSpriteAnimation
{
public:
	WeaponWhip(CVGame *game, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~WeaponWhip();

	void SetWhipVersion(int version);
	void UpgradeWhip();
	void ResetWhip() { this->whipVersion = 1; }
	void Attack(bool isLeft);
	void Draw();
	void UpdateWorldPosition() override;

private:
	int whipVersion;	// 1, 2, 3
};

