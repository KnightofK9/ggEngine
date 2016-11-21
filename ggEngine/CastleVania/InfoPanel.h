#pragma once
#include <ggEngine.h>
#include "HealthBar.h"
using namespace ggEngine;
class InfoPanel : public ScreenGroup {
public:
	InfoPanel(DrawManager* drawManager);
	~InfoPanel();
	virtual void Draw() override;
	void SetPlayerHealth();
	void SetEnemyHealth();
	void SetLife();
	void SetPoint();
	void SetState();
	void SetScore();

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

	TimeBasedEventInfo* timeInfo;
	int curTime = 300;
private:
	void GetTime();
};