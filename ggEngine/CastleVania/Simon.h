#pragma once
#include <ggEngine.h>
#include "CharacterBase.h"
#include "CharacterConstant.h"
#include "InfoPanel.h"
using namespace ggEngine;
class CVGame;
class ItemBase;
class Simon :public CharacterBase {
public:
	Simon(CVGame *cvGame, SpriteInfo *image, InfoPanel *infoPanel, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~Simon();
	void SetHealth(int heath);
	int GetHealth() { return this->health; }
	
	void SetMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
	int GetMaxHealth() { return this->maxHealth; }


	void Idle();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Kneel();
	void ClimbUp();
	void ClimbDown();
	void Hurt();
	void Death();
	void StandAttack();
	void KneelAttack();
	void ClimbDownAttack();
	void ClimbUpAttack();
	void LoseHealth(int health);
	void GainHealth(int health);

	void *HealthDown(int health) { this->health -= health; }

	InfoPanel *infoPanel = nullptr;
	bool isGrounding;	//for jump or for fall down or for hurt
private:
	int health;
	int maxHealth;
	int score;
	ItemBase * currentItem = nullptr;
};