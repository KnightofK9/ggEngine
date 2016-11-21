#pragma once
#include <ggEngine.h>
#include "CVState.h"

class IntroState : public CVState {
public:
	IntroState(CVGame *game);
	~IntroState();
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
	Sprite* menu_bg;
	SpriteAnimation* menu_anim;
	Text* push;
	Text* year;
	Text* coLTD;
	Text* licenceBy;
	Text* INC;
};