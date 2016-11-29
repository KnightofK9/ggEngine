#pragma once
#include <ggEngine.h>
#include "CVState.h"

class GameOverState : public CVState {
public:
	GameOverState(CVGame *game);
	~GameOverState();
	void Init(); //Called after start a scene
	void Preload(); //Called after int
	void Create();//Called after preload complete
	void Update();//Called before each game update loop
	void PreRender();//Called before enter each render
	void Render();//Called after render completed
	void Pause();//Called when the scene is set to paused
	void Resume();//Called when the scene is resumed
	void ShutDown();
	//Called when start a new scene
private:
	void ChangeState();
	void ToggleHeart(bool up);

	Text *gameOver;
	Text *cont;
	Text *end;
	Sprite *heart;	//to choose continue or end.

	bool isKeyPressed = false;
	bool isToggleUp = false;
};