#pragma once
#include <ggEngine.h>
#include "CVSpriteAnimation.h"
#include "CVSprite.h"
#include "ManagerBase.h"
using namespace ggEngine;
class AnimationManager : ManagerBase {
public:
	AnimationManager(CVGame *cvGame);
	~AnimationManager();

	void PreloadAll();

	CVSpriteAnimation* AddEnemyDeathAnimation(double x, double y);
	CVSpriteAnimation* AddBossDeathAnimation(double x, double y);
	CVSpriteAnimation* AddHitAnimation(double x, double y);
	CVSprite** AddBreakingWallAnimation(double x, double y);

	Group* simonGroup = nullptr;
private:
};