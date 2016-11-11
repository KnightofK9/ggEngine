#pragma once
#include "../ggEngine/ggEngine.h"
using namespace ggEngine;
class TestStateCastleVania : public State{
public:
	TestStateCastleVania(Game *game);
	~TestStateCastleVania();
	void Init(); //Called after start a scene
	void Preload(); //Called after int
	void Create();//Called after preload complete
	void Update();//Called before each game update loop
	void PreRender();//Called before enter each render
	void Render();//Called after render completed
	void Pause();//Called when the scene is set to paused
	void Resume();//Called when the scene is resumed
	void ShutDown();//Called when start a new scene
private:
	SpriteAnimation *character;
	Group *group;
	const double charMoveSpeed = 10.0f;
	const double jumpForce = 5.0f;
	const double jumpTime = 500;
	TileMap *tileMap;
	Grid *grid;
	Timer jumpTimer;
};