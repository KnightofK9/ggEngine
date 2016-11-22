#pragma once
#include <ggEngine.h>
#include "CharacterBase.h"
#include "CharacterConstant.h"
#include "InfoPanel.h"
#include <boost\signals2.hpp>
using namespace ggEngine;

class Simon :public CharacterBase {
public:
	boost::signals2::signal<void(int)> healthSignal;

	Simon(DrawManager *drawManager, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~Simon();
	void SetHealth(int heath);
	int GetHealth() { return this->health; }
	
	void Idle();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void Kneel();
	void Climbup();
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
};