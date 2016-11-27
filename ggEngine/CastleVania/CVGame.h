#pragma once
#include <ggEngine.h>
using namespace ggEngine;
class CVAdd;
class CVPreload;
class Simon;
class CVGame : public Game {
public:
	CVGame(HWND hWnd, int width, int height, GameMode mode = GameMode_Windowed, PhysicsMode physicsMode = PhysicsMode_AABB, D3DCOLOR gameColor = D3DCOLOR_XRGB(0, 255, 255));
	~CVGame();
	CVAdd *cvAdd;
	CVPreload *cvPreload;
	Simon *simon;
private:
};