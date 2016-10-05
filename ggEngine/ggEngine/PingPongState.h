#pragma once
#include "State.h"
#include "Timer.h"
#include "Text.h"

using namespace ggEngine;
class PingPongState : public State {
private:
	Sprite *ball, *leftBat, *rightBat;
	Group* group;
	long score1, score2;
	Text *textScore1, *textScore2;

	SpriteAnimation *sprite1;
	SpriteAnimation *sprite4;
	float test = 0.01f;
	Sprite *background;
	float MoveSpeedPerSec = 400.0f;
	Timer shootTimer;
	float shootTime = 1000.0f;

public:
	PingPongState(Game *game);
	~PingPongState();
	void Init(); //Called after start a scene
	void Preload(); //Called after int
	void Create();//Called after preload complete
	void Update();//Called before each game update loop
	void PreRender();//Called before enter each render
	void Render();//Called after render completed
	void Pause();//Called when the scene is set to pausde
	void Resume();//Called when the scene is resumed
	void ShutDown();//Called when start a new scene
};