#pragma once
#include <ggEngine.h>
#include "CVState.h"

class GameOverScreen : public ScreenGroup {
public:
	GameOverScreen(CVGame *game);
	virtual ~GameOverScreen();
	virtual void Draw() override;
	void ToggleHeart(bool up);
	void SetEventToggleHeart(std::function<void(void)> onToggleUp, std::function<void(void)> onToggleDown);
	void SetVisibility(bool isVisible);

	Text *gameOver;
	Text *cont;
	Text *end;
	Sprite *heart;	//to choose continue or end.

	bool isKeyPressed = false;
	bool isToggleUp = false;

	std::function<void(void)> onToggleUp;
	std::function<void(void)> onToggleDown;

private:
};