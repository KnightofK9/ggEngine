#pragma once
#include <ggEngine.h>
#include "HealthBar.h"
using namespace ggEngine;
class InfoPanel : public ScreenGroup {
public:
	InfoPanel(DrawManager* drawManager);
	~InfoPanel();
	virtual void Draw() override;
	void SetPlayerHealth(int health);
	void SetEnemyHealth(const int& health);
	void SetLife(const int& point);
	void SetPoint(const int& point);
	void SetState(const int& state);
	void SetScore(const int& score);

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
	SpriteInfo *itemInfo = nullptr;

	TimeBasedEventInfo* timeInfo = nullptr;
private:
	int curTime = 100;
};