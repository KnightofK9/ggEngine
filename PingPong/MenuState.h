#pragma once
#include "GlobalHeader.h"
using namespace ggEngine;
class MenuState : public State {
private:
	Sprite* background;
	Group* menuGroup;
public:
	MenuState(Game *game);
	~MenuState();
	void Init(); //Called after start a scene
	void Preload(); //Called after int
	void Create();//Called after preload complete
	void Update();//Called before each game update loop
	void PreRender();//Called before enter each render
	void Render();//Called after render completed
	void Pause();//Called when the scene is set to paused
	void Resume();//Called when the scene is resumed
	void ShutDown();//Called when start a new scene
};