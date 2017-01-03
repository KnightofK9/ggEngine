#pragma once
#include <ggEngine.h>

using namespace ggEngine;
class CVGame;
class GameOverScreen : public ScreenGroup {
public:
	GameOverScreen(CVGame *game);
	virtual ~GameOverScreen();
	virtual void Draw() override;
	void ToggleHeart(bool isUp);
	void SetEnable(bool isEnable);
	void SetEnableEventToggleHeart();

	Text *gameOver;
	Text *cont;
	Text *end;
	Sprite *heart;	//to choose continue or end.

	bool isKeyPressed = false;
	bool isToggleUp = false;

	//std::function<void(void)> onToggleUp;
	//std::function<void(void)> onToggleDown;

private:
	CVGame *cvGame = nullptr;
	bool isEnableKey;
};