#pragma once
#include <ggEngine.h>
#include "CVAdd.h"
#include "CVPreload.h"
using namespace ggEngine;
class CVState : public State {
public :
	CVState(Game *game);
	CVState(Game *game,Json state);
	~CVState();
	virtual void Init() ; //Called after start a State
	virtual void Preload() ; //Called after init
	virtual void Create() ;//Called after preload complete
	virtual void Update();//Called before each game update loop
	virtual void PreRender();//Called before enter each render
	virtual void Render();//Called after render completed
	virtual void Pause();//Called when the game is set to paused
	virtual void Resume();//Called when the game is resumed
	virtual void ShutDown();//Called when start a new State
	void Load() override;
protected:
	std::string json;
};