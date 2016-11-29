#pragma once

#include <ggEngine.h>
using namespace ggEngine;
class HealthBar : public ScreenGroup {
public:
	HealthBar(DrawManager *drawManager);
	~HealthBar();
	int GetHealth() { return this->currentHealth; }
	void SetHealth(int currentHealth);
	void SetEmptyHealthBar(Sprite *emptyHealthBar);
	void SetHealthBar(Sprite *healthBar, int maxHealth);
	void Draw() override;


private:
	Sprite* healthBar = nullptr;
	Sprite* emptyHealthBar = nullptr;
	int maxHealth;
	int currentHealth;
	int originWidth;
};