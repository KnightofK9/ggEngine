#pragma once
#include <ggEngine.h>
#include "CVAdd.h"
#include "CVPreload.h"
#include "CVGame.h"
using namespace ggEngine;
class CVState : public State {
public :
	CVState(CVGame *game);
	CVState(CVGame *game, std::string statePath);
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
	virtual void Load() override;
	CVAdd *cvAdd = nullptr;
	CVPreload *cvPreload = nullptr;
protected:
	std::string json;
	CVGame *cvgame;
};