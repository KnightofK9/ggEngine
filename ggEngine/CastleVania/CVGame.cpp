#include "CVGame.h"
#include "CVAdd.h"
#include "CVPreload.h"
CVGame::CVGame(HWND hWnd, int width, int height, GameMode mode, PhysicsMode physicsMode, D3DCOLOR gameColor) :Game(hWnd, width, height, mode, physicsMode, gameColor)
{
	this->cvPreload = new CVPreload(this->cache);
	this->cvAdd = new CVAdd(nullptr, this);
}

CVGame::~CVGame()
{
}
