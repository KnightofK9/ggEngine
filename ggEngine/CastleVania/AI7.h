#pragma once
#include "TweenEnemyBase.h"
class AI7 : public TweenEnemyBase {
public:
	AI7(CVGame *cvGame, SpriteInfo *spriteInfo);
	virtual ~AI7();

	void RunLeft() override;
	void RunRight() override;
	void Update() override;
	void Active() override;
	void SetPosition(Vector position, bool isRefresh = false) override;
	void Draw() override;
private:
	bool isRunning;
	bool isRunUp;
	Vector spawnPosition;
	Vector upLimitPosition;
	double rigidBodyHeight;
};