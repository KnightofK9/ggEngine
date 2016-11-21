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
	void SetEnemyHealth(int health);
	void SetLife(int point);
	void SetPoint(int point);
	void SetState(int state);
	void SetScore(int score);

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

	TimeBasedEventInfo* timeInfo = nullptr;
	int curTime = 300;

private:
};