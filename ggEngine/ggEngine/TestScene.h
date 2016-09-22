#pragma once
#include "Scene.h"
using namespace ggEngine;
class TestScene : public Scene{
public:
	void Init();
	void Preload();
	void Destroy();
	void LoadComplete();
};