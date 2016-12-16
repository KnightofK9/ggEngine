#pragma once
#include <ggEngine.h>
#include "HealthBar.h"
#include "GameOverScreen.h"

class CVGame;
using namespace ggEngine;
class InfoPanel : public ScreenGroup {
public:
	InfoPanel(GameOverScreen *goScreen, CVGame *cvGame);
	virtual ~InfoPanel();
	virtual void Draw() override;
	void SetPlayerHealth(int health);
	void SetEnemyHealth(const int& health);
	void SetHeartPoint(const int& point);
	void SetPPoint(const int& point);
	void SetStatePoint(const int& state);
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
	int curTime = 100;
	CVGame *cvGame = nullptr;
	std::function<void(void)> onTimeUp;
	TimeBasedEventInfo* timeInfo = nullptr;
	GameOverScreen *goScreen = nullptr;
};