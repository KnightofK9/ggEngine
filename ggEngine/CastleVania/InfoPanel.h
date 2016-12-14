#pragma once
#include <ggEngine.h>
#include "HealthBar.h"
class CVGame;
using namespace ggEngine;
class InfoPanel : public ScreenGroup {
public:
	InfoPanel(CVGame *cvGame);
	virtual ~InfoPanel();
	virtual void Draw() override;
	void SetPlayerHealth(int health);
	void SetEnemyHealth(const int& health);
	void SetLife(const int& point);
	void SetPoint(const int& point);
	void SetState(const int& state);
	void SetScore(const int& score);
	void SetItemImage(SpriteInfo *spriteInfo);
	TimeBasedEventInfo* CountDown(int timeBegin, std::function<void(void)> onTimeUp);

	void StopTime();
	void StartTime();
	void SetTime(const int& time);
	int GetTime() { return curTime; }

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

	Sprite* lifeIcon = nullptr;
	Text *life = nullptr;
	Text *lifePoint = nullptr;

	Text *p = nullptr;
	Text *pPoint = nullptr;

	HealthBar *playerHealthBar = nullptr;
	HealthBar *enemyHealthBar = nullptr;

	Sprite *itemBox = nullptr;
	Sprite *item = nullptr;
	Sprite *itemShot = nullptr;

private:
	int curTime = 100;
	CVGame *cvGame = nullptr;
	std::function<void(void)> onTimeUp;
	TimeBasedEventInfo* timeInfo = nullptr;
};