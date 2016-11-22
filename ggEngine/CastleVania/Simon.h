#pragma once
#include <ggEngine.h>
#include "CharacterBase.h"
#include "InfoPanel.h"
using namespace ggEngine;
class Simon :public CharacterBase {
public:
	Simon(DrawManager *drawManager, SpriteInfo *image, int frameWidth, int frameHeight, int defaultFrame = 0, int numberOfFrame = 0, DWORD msPerFrame = DEFAULT_MS_PER_FRAME_FOR_ANIMATION);
	~Simon();
	void SetHealth(int heath);
	int GetHealth() { return 100; }// this->health; }

	InfoPanel *infoPanel = nullptr;
	bool isGrounding;	//for jump or for fall down or for hurt
private:
	int health;
};