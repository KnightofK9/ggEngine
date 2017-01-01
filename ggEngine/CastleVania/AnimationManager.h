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

	CVSpriteAnimation* AddText100(double x, double y);
	CVSpriteAnimation* AddText400(double x, double y);
	CVSpriteAnimation* AddText700(double x, double y);
	CVSpriteAnimation* AddText1000(double x, double y);
	CVSpriteAnimation* AddText2000(double x, double y);
	CVSpriteAnimation* AddEnemyDeathAnimation(double x, double y);
	CVSpriteAnimation* AddBossDeathAnimation(double x, double y);
	CVSpriteAnimation* AddHitAnimation(double x, double y);
	CVSprite** AddBreakingWallAnimation(double x, double y);

	Group* simonGroup = nullptr;
private:
};