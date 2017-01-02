#pragma once
#include <ggEngine.h>
#include "HealthBar.h"
#include "StateConstant.h"

class CVGame;
class EnemyBase;
using namespace ggEngine;
class InfoPanel : public ScreenGroup {
public:
	InfoPanel(CVGame *cvGame);
	virtual ~InfoPanel();
	virtual void Draw() override;
	void SetPlayerHealth(int health);
	void SetEnemyHealth(const int& health);
	void SetHeartPoint(const int& point);
	void SetPPoint(const int& point);
	void SetStatePoint(const int& state);
	void SetScore(const int& score);
	void SetItemImage(SpriteInfo *spriteInfo);
	TimeBasedEventInfo* CountDown(int duration, std::function<void(void)> onTimeUp);

	void StopCountDownTime();
	void StartCountDownTime();
	void SetTime(const int& time);
	int GetTime() { return maxTime; }
	void SetEnemy(EnemyBase *enemyBase);
	void Reset();
	Text *score = nullptr;
	Text *scorePoint = nullptr;

	Text *time = nullptr;
	Text *timePoint = nullptr;

	Text *stage = nullptr;
	Text *stagePoint = nullptr;

	Text *player = nullptr;
	Text *playerPoint = nullptr;

	Text *enemy = nullptr;
	Text *enemyPoint = nullptr;

	Sprite* heartIcon = nullptr;
	Text *heart = nullptr;
	Text *heartPoint = nullptr;

	Text *p = nullptr;
	Text *pPoint = nullptr;

	HealthBar *playerHealthBar = nullptr;
	HealthBar *enemyHealthBar = nullptr;

	Sprite *itemBox = nullptr;
	Sprite *item = nullptr;
	Sprite *itemShot = nullptr;

private:
	EnemyBase* enemyBase = nullptr;
	int maxTime = StateConstant::MAX_TIME_IN_LEVEL_1;
	CVGame *cvGame = nullptr;
	std::function<void(void)> onTimeUp;
	TimeBasedEventInfo* timeInfo = nullptr;
};