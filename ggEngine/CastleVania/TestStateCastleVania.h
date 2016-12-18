#pragma once
#include <ggEngine.h>
#include "CVState.h"
#include "Simon.h"
#include "CVMap.h"
using namespace ggEngine;
class TestStateCastleVania : public CVState{
public:
	TestStateCastleVania(CVGame *game);
	virtual ~TestStateCastleVania();
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
	TileMap *tileMap;
	Simon *simon;
	ItemManager *itemManager = nullptr;
	CVMap *cvMap = nullptr;
	CVMap *cvMap1 = nullptr;
	CVMap *cvMap2 = nullptr;
};